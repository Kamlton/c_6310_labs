//Вывести символ	Печатаем 1 символ в файл/консоль	'A',1→A
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}