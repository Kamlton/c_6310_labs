// Проверка на букву	Это буква A-Z или a-z?	'A'→1, '1'→0
#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}