//Поиск подстроки	Есть ли подстрока в строке?	"Hello","el"→"ello"
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	if (!*little)
		return ((char *)big);
	little_len = ft_strlen(little);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len && little[j])
			j++;
		if (j == little_len)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}