//Проверка на цифру	Это цифра 0-9?	'5'→1, 'A'→0
#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}