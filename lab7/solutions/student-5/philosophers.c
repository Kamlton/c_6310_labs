#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
** Обычный enum для состояния философа
*/
typedef enum e_state
{
    THINKING,
    HUNGRY,
    EATING
}   t_state;

/*
** Флаговый enum для отслеживания вилок в руках философа
** Используем битовые флаги для комбинации состояний
*/
typedef enum e_philo_flags
{
    PHILO_NONE      = 0,
    PHILO_HAS_LEFT  = 1 << 0,  // 1 (бит 0)
    PHILO_HAS_RIGHT = 1 << 1   // 2 (бит 1)
}   t_philo_flags;

/*
** Структура философа
*/
typedef struct s_philosopher
{
    int             id;                // Номер философа (1-5)
    t_state         state;             // Текущее состояние
    t_philo_flags   flags;             // Какие вилки держит (битовая маска)
    pthread_t       thread;            // Идентификатор потока
    pthread_mutex_t *left_fork;        // Указатель на левую вилку
    pthread_mutex_t *right_fork;       // Указатель на правую вилку
    int             meals_eaten;       // Счётчик съеденных порций
    int             max_meals;         // Максимальное количество приёмов пищи
}   t_philosopher;

/*
** Глобальные данные в структуре (вместо глобальных переменных)
*/
typedef struct s_table
{
    t_philosopher   *philosophers;
    pthread_mutex_t *forks;
    int             num_philosophers;
    int             max_meals;
}   t_table;

/*
** Мьютекс для защиты вывода в консоль
*/
static pthread_mutex_t g_print_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
** Функция безопасного вывода сообщений
*/
static void safe_print(t_philosopher *philo, const char *action)
{
    pthread_mutex_lock(&g_print_mutex);
    printf("Philosopher %d is %s\n", philo->id, action);
    pthread_mutex_unlock(&g_print_mutex);
}

/*
** Философ думает
*/
static void think(t_philosopher *philo)
{
    if (philo->state != THINKING)
    {
        philo->state = THINKING;
        philo->flags = PHILO_NONE;
        safe_print(philo, "THINKING");
    }
    usleep(100000); // 100 мс размышлений
}

/*
** Философ ест
*/
static void eat(t_philosopher *philo)
{
    if (philo->state != EATING)
    {
        philo->state = EATING;
        safe_print(philo, "EATING");
        philo->meals_eaten++;
    }
    usleep(100000); // 100 мс еды
}

/*
** Захват вилок с предотвращением deadlock
** Чётные философы: сначала левая, потом правая
** Нечётные философы: сначала правая, потом левая
*/
static void take_forks(t_philosopher *philo)
{
    if (philo->state == HUNGRY)
        return;
    
    philo->state = HUNGRY;
    safe_print(philo, "HUNGRY");
    
    if (philo->id % 2 == 0)
    {
        /* Чётные: левая -> правая */
        pthread_mutex_lock(philo->left_fork);
        philo->flags |= PHILO_HAS_LEFT;
        safe_print(philo, "took left fork");
        
        pthread_mutex_lock(philo->right_fork);
        philo->flags |= PHILO_HAS_RIGHT;
        safe_print(philo, "took right fork");
    }
    else
    {
        /* Нечётные: правая -> левая */
        pthread_mutex_lock(philo->right_fork);
        philo->flags |= PHILO_HAS_RIGHT;
        safe_print(philo, "took right fork");
        
        pthread_mutex_lock(philo->left_fork);
        philo->flags |= PHILO_HAS_LEFT;
        safe_print(philo, "took left fork");
    }
}

/*
** Освобождение вилок
*/
static void put_forks(t_philosopher *philo)
{
    if (philo->flags & PHILO_HAS_LEFT)
    {
        pthread_mutex_unlock(philo->left_fork);
        philo->flags &= ~PHILO_HAS_LEFT;
    }
    
    if (philo->flags & PHILO_HAS_RIGHT)
    {
        pthread_mutex_unlock(philo->right_fork);
        philo->flags &= ~PHILO_HAS_RIGHT;
    }
    
    if (philo->flags == PHILO_NONE)
        safe_print(philo, "put forks");
}

/*
** Основной цикл философа (потоковая функция)
*/
static void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    
    while (philo->meals_eaten < philo->max_meals)
    {
        think(philo);
        take_forks(philo);
        eat(philo);
        put_forks(philo);
    }
    
    safe_print(philo, "FINISHED (max meals reached)");
    return (NULL);
}

/*
** Инициализация стола (философы и вилки)
*/
static int init_table(t_table *table, int num_philosophers, int max_meals)
{
    int i;
    
    table->num_philosophers = num_philosophers;
    table->max_meals = max_meals;
    
    /* Выделение памяти под мьютексы (вилки) */
    table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_philosophers);
    if (!table->forks)
        return (0);
    
    /* Инициализация мьютексов для вилок */
    i = 0;
    while (i < num_philosophers)
    {
        if (pthread_mutex_init(&table->forks[i], NULL) != 0)
        {
            while (--i >= 0)
                pthread_mutex_destroy(&table->forks[i]);
            free(table->forks);
            return (0);
        }
        i++;
    }
    
    /* Выделение памяти под философов */
    table->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) * num_philosophers);
    if (!table->philosophers)
    {
        i = 0;
        while (i < num_philosophers)
            pthread_mutex_destroy(&table->forks[i++]);
        free(table->forks);
        return (0);
    }
    
    /* Инициализация философов */
    i = 0;
    while (i < num_philosophers)
    {
        table->philosophers[i].id = i + 1;
        table->philosophers[i].state = THINKING;
        table->philosophers[i].flags = PHILO_NONE;
        table->philosophers[i].left_fork = &table->forks[i];
        table->philosophers[i].right_fork = &table->forks[(i + 1) % num_philosophers];
        table->philosophers[i].meals_eaten = 0;
        table->philosophers[i].max_meals = max_meals;
        i++;
    }
    
    return (1);
}

/*
** Запуск потоков философов
*/
static int start_dinner(t_table *table)
{
    int i;
    
    i = 0;
    while (i < table->num_philosophers)
    {
        if (pthread_create(&table->philosophers[i].thread, NULL,
                          philosopher_routine, &table->philosophers[i]) != 0)
        {
            while (--i >= 0)
                pthread_join(table->philosophers[i].thread, NULL);
            return (0);
        }
        i++;
    }
    
    return (1);
}

/*
** Ожидание завершения всех потоков
*/
static void wait_for_philosophers(t_table *table)
{
    int i;
    
    i = 0;
    while (i < table->num_philosophers)
    {
        pthread_join(table->philosophers[i].thread, NULL);
        i++;
    }
}

/*
** Очистка всех ресурсов
*/
static void cleanup_table(t_table *table)
{
    int i;
    
    if (table->philosophers)
        free(table->philosophers);
    
    if (table->forks)
    {
        i = 0;
        while (i < table->num_philosophers)
        {
            pthread_mutex_destroy(&table->forks[i]);
            i++;
        }
        free(table->forks);
    }
}

/*
** Главная функция
*/
int main(void)
{
    t_table table;
    int     num_philosophers = 5;
    int     max_meals = 3;
    
    printf("========================================\n");
    printf("Обедающие философы\n");
    printf("========================================\n");
    printf("Философов: %d\n", num_philosophers);
    printf("Каждый поест: %d раз(а)\n", max_meals);
    printf("========================================\n\n");
    
    /* Инициализация */
    if (!init_table(&table, num_philosophers, max_meals))
    {
        printf("ОШИБКА: Не удалось инициализировать структуры\n");
        return (1);
    }
    
    /* Запуск обеда */
    if (!start_dinner(&table))
    {
        printf("ОШИБКА: Не удалось создать потоки\n");
        cleanup_table(&table);
        return (1);
    }
    
    /* Ожидание завершения философов */
    wait_for_philosophers(&table);
    
    /* Вывод результатов */
    printf("\n========================================\n");
    printf("РЕЗУЛЬТАТЫ\n");
    printf("========================================\n");
    for (int i = 0; i < num_philosophers; i++)
    {
        printf("Философ %d поел %d раз(а)\n",
               table.philosophers[i].id,
               table.philosophers[i].meals_eaten);
    }
    printf("========================================\n");
    
    /* Очистка ресурсов */
    cleanup_table(&table);
    
    return (0);
}