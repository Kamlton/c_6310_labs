#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

/*
** Базовые функции, используемые в калькуляторе
*/

// Преобразование строки в число
int		ft_atoi(const char *str);

// Сравнение строк
int		ft_strcmp(const char *s1, const char *s2);

// Длина строки
size_t	ft_strlen(const char *s);

// Вывод символа
void	ft_putchar_fd(char c, int fd);

// Вывод строки
void	ft_putstr_fd(char *s, int fd);

// Вывод строки с переводом строки
void	ft_putendl_fd(char *s, int fd);

// Вывод числа
void	ft_putnbr_fd(int n, int fd);

// Выделение памяти с обнулением
void	*ft_calloc(size_t count, size_t size);

// Копирование строки
char	*ft_strdup(const char *s1);

// Поиск подстроки (если понадобится)
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

// Сравнение строк с ограничением (вместо ft_strcmp, если нет)
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif