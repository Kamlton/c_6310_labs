//Буква или цифра	Это буква ИЛИ цифра?	'A'→1, '5'→1, '@'→0
#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}