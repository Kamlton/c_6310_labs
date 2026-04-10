//Длина строки	Сколько символов до \0?	"Hello"→5, ""→0
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}