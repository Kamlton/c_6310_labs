//Проверка ASCII	Код от 0 до 127?	65→1, 200→0
#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}