//Печатный символ	Можно напечатать? (32-126)	' '→1, '\n'→0
#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}