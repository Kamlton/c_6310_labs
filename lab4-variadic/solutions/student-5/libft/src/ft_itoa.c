//Число → строка	123 превращаем в "123"	-42→"-42"
#include "libft.h"

static int	num_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	fill_str(char *str, int n, int len, int is_negative)
{
	str[len] = '\0';
	if (is_negative)
	{
		str[0] = '-';
		n = -n;
	}
	while (len-- > is_negative)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		is_negative;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = num_len(n);
	is_negative = (n < 0);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	fill_str(str, n, len, is_negative);
	return (str);
}