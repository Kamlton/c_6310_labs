//Поиск символа справа	Где символ в последний раз?	"Hello",'l'→"lo"
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	char	ch;

	ch = (char)c;
	last = NULL;
	while (*s)
	{
		if (*s == ch)
			last = (char *)s;
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (last);
}