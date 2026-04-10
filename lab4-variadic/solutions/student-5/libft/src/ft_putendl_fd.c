//Вывести строку + \n	Печатаем строку и переводим строку	"Hello",1→Hello\n
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}