#include "libft.h"
#include <stdarg.h>

typedef struct s_operation
{
    char *name;
    int (*func)(int count, ...);
} t_operation;

int sum(int count, ...)
{
    va_list args;
    int total = 0;
    int i;

    va_start(args, count);
    i = 0;
    while (i < count)
    {
        total += va_arg(args, int);
        i++;
    }
    va_end(args);
    return (total);
}

int mul(int count, ...)
{
    va_list args;
    int product = 1;
    int i;

    va_start(args, count);
    i = 0;
    while (i < count)
    {
        product *= va_arg(args, int);
        i++;
    }
    va_end(args);
    return (product);
}

int avg(int count, ...)
{
    va_list args;
    int sum_val = 0;
    int i;

    va_start(args, count);
    i = 0;
    while (i < count)
    {
        sum_val += va_arg(args, int);
        i++;
    }
    va_end(args);
    return (sum_val / count);
}

static t_operation g_operations[] = {
    {"sum", sum},
    {"mul", mul},
    {"avg", avg},
    {NULL, NULL}
};

static int (*find_operation(const char *name))(int, ...)
{
    int i;

    i = 0;
    while (g_operations[i].name)
    {
        if (ft_strncmp(g_operations[i].name, name, ft_strlen(name) + 1) == 0)
            return (g_operations[i].func);
        i++;
    }
    return (NULL);
}

static void print_error(const char *msg)
{
    ft_putstr_fd("Ошибка: ", 2);
    ft_putstr_fd((char *)msg, 2);
    ft_putchar_fd('\n', 2);
}

static void print_usage(const char *prog_name)
{
    ft_putstr_fd("Использование: ", 2);
    ft_putstr_fd((char *)prog_name, 2);
    ft_putstr_fd(" <операция> [числа...]\n", 2);
    ft_putstr_fd("Операции: sum, mul, avg\n", 2);
    ft_putstr_fd("Пример: ", 2);
    ft_putstr_fd((char *)prog_name, 2);
    ft_putstr_fd(" sum 1 2 3\n", 2);
}

static void free_numbers(void *ptr)
{
    if (ptr)
        free(ptr);
}

int main(int argc, char **argv)
{
    int (*operation)(int, ...);
    int *numbers;
    int count;
    int result;
    int i;

    if (argc < 3)
    {
        print_error("Недостаточно аргументов. Укажите операцию и хотя бы одно число.");
        print_usage(argv[0]);
        return (1);
    }

    operation = find_operation(argv[1]);
    if (!operation)
    {
        print_error("Неизвестная операция. Доступные операции: sum, mul, avg");
        print_usage(argv[0]);
        return (1);
    }

    count = argc - 2;

    numbers = (int *)ft_calloc(count, sizeof(int));
    if (!numbers)
    {
        print_error("Ошибка выделения памяти");
        return (1);
    }

    i = 0;
    while (i < count)
    {
        numbers[i] = ft_atoi(argv[i + 2]);
        i++;
    }

    if (count == 1)
        result = operation(1, numbers[0]);
    else if (count == 2)
        result = operation(2, numbers[0], numbers[1]);
    else if (count == 3)
        result = operation(3, numbers[0], numbers[1], numbers[2]);
    else if (count == 4)
        result = operation(4, numbers[0], numbers[1], numbers[2], numbers[3]);
    else if (count == 5)
        result = operation(5, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]);
    else
    {
        free_numbers(numbers);
        print_error("Поддерживается до 5 чисел для наглядности демонстрации вариативных функций");
        return (1);
    }

    ft_putnbr_fd(result, 1);
    ft_putchar_fd('\n', 1);

    free_numbers(numbers);
    return (0);
}