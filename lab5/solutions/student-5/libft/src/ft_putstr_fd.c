//Вывести строку	Печатаем строку в файл/консоль	"Hello",1→Hello
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}