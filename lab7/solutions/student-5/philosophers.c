#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef enum e_state { THINKING, HUNGRY, EATING } t_state;
typedef enum e_philo_flags { PHILO_NONE = 0, PHILO_HAS_LEFT = 1, PHILO_HAS_RIGHT = 2 } t_philo_flags;

typedef struct s_philosopher
{
    int             id;
    t_state         state;
    t_philo_flags   flags;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    int             meals_eaten;
    int             max_meals;
    pthread_mutex_t *print_mutex;
}   t_philosopher;

static void safe_print(t_philosopher *philo, const char *msg)
{
    pthread_mutex_lock(philo->print_mutex);
    printf("Philosopher %d %s\n", philo->id, msg);
    pthread_mutex_unlock(philo->print_mutex);
}

static void thinking(t_philosopher *philo)
{
    if (philo->state != THINKING)
    {
        philo->state = THINKING;
        philo->flags = PHILO_NONE;
        safe_print(philo, "is THINKING");
    }
    usleep(80000);
}

static void eating(t_philosopher *philo)
{
    if (philo->state != EATING)
    {
        philo->state = EATING;
        safe_print(philo, "is EATING");
        philo->meals_eaten++;
    }
    usleep(80000);
}

static void take_forks(t_philosopher *philo)
{
    if (philo->state == HUNGRY)
        return;
    
    philo->state = HUNGRY;
    safe_print(philo, "is HUNGRY");
    
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        philo->flags |= PHILO_HAS_LEFT;
        safe_print(philo, "took left fork");
        
        pthread_mutex_lock(philo->right_fork);
        philo->flags |= PHILO_HAS_RIGHT;
        safe_print(philo, "took right fork");
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        philo->flags |= PHILO_HAS_RIGHT;
        safe_print(philo, "took right fork");
        
        pthread_mutex_lock(philo->left_fork);
        philo->flags |= PHILO_HAS_LEFT;
        safe_print(philo, "took left fork");
    }
}

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
        safe_print(philo, "put both forks");
}

static void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    
    while (philo->meals_eaten < philo->max_meals)
    {
        thinking(philo);
        take_forks(philo);
        eating(philo);
        put_forks(philo);
    }
    
    safe_print(philo, "FINISHED eating");
    return (NULL);
}

int main(void)
{
    pthread_mutex_t     forks[5];
    pthread_mutex_t     print_mutex;
    t_philosopher       philosophers[5];
    int                 i;
    int                 num_philosophers = 5;
    int                 max_meals = 3;
    
    printf("========================================\n");
    printf("Dining Philosophers Problem\n");
    printf("========================================\n");
    printf("Philosophers: %d\n", num_philosophers);
    printf("Each will eat: %d time(s)\n", max_meals);
    printf("========================================\n\n");
    
    pthread_mutex_init(&print_mutex, NULL);
    
    i = 0;
    while (i < num_philosophers)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    
    i = 0;
    while (i < num_philosophers)
    {
        philosophers[i].id = i + 1;
        philosophers[i].state = THINKING;
        philosophers[i].flags = PHILO_NONE;
        philosophers[i].left_fork = &forks[i];
        philosophers[i].right_fork = &forks[(i + 1) % num_philosophers];
        philosophers[i].meals_eaten = 0;
        philosophers[i].max_meals = max_meals;
        philosophers[i].print_mutex = &print_mutex;
        i++;
    }
    
    i = 0;
    while (i < num_philosophers)
    {
        pthread_create(&philosophers[i].thread, NULL, philosopher_routine, &philosophers[i]);
        i++;
    }
    
    i = 0;
    while (i < num_philosophers)
    {
        pthread_join(philosophers[i].thread, NULL);
        i++;
    }
    
    printf("\n========================================\n");
    printf("RESULTS\n");
    printf("========================================\n");
    i = 0;
    while (i < num_philosophers)
    {
        printf("Philosopher %d ate %d time(s)\n", philosophers[i].id, philosophers[i].meals_eaten);
        i++;
    }
    printf("========================================\n");
    
    i = 0;
    while (i < num_philosophers)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    pthread_mutex_destroy(&print_mutex);
    
    return (0);
}