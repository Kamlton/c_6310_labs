//В нижний регистр	БОЛЬШУЮ букву → маленькую	'A'→'a', 'a'→'a'
#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}