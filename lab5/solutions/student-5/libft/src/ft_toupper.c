//В верхний регистр	Маленькую букву → БОЛЬШУЮ	'a'→'A', 'A'→'A'
#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}