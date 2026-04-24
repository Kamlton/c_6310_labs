//Разбить строку	Делим по разделителю	"a b c",' '→["a","b","c",NULL]
#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*get_word(char const *s, char c)
{
	char	*word;
	int		len;
	int		i;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_split(char **split, int index)
{
	while (index >= 0)
	{
		free(split[index]);
		index--;
	}
	free(split);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < words)
	{
		if (s[i] != c)
		{
			result[j] = get_word(&s[i], c);
			if (!result[j])
				return (free_split(result, j - 1), NULL);
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	result[j] = NULL;
	return (result);
}