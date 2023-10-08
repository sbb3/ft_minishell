
#include "source_.h"

static int	ft_words(const char *s, char c)
{
	int	l;

	l = 0;
	while (*s && *s == c)
		s++;
	if (! *s)
		return (l);
	while (*s)
	{
		if (*s == c)
			l++;
		while (*s && *s == c)
			s++;
		if (! *s)
			return (l);
		s++;
	}
	return (l + 1);
}

static int	ft_setword(const char *str, char **strings, char c, int i)
{
	int		len;
	int		j;
	char	*s;

	j = 0;
	len = 0;
	while (str[i] == c)
		i++;
	while (str[i + len] != c && str[i + len])
		len++;
	s = malloc(len + 1);
	if (! s)
		return (-1);
	while (str[i] && str[i] != c)
		s[j++] = str[i++];
	s[j] = 0;
	*strings = s;
	return (i);
}

static void	ft_free_strings(char **s, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(s[i++]);
	free(s);
}

static char	**ft_split_subprocess(const char *str, char c, int l)
{
	char	**s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s = malloc((l + 1) * sizeof(char *));
	if (! s)
		return (NULL);
	while (j < l)
	{
		i = ft_setword(str, s + j, c, i);
		if (i == -1)
		{
			ft_free_strings(s, j);
			j = 0;
			break ;
		}
		j++;
	}
	s[j] = 0;
	return (s);
}

char	**ft_split(const char *str, char c)
{
	char	**s;
	int		len;

	if (! str)
	{
		s = malloc(sizeof(char *));
		s[0] = NULL;
		return (s);
	}
	len = ft_words(str, c);
	if (! len)
	{
		s = malloc(sizeof(char *));
		s[0] = NULL;
		return (s);
	}
	s = ft_split_subprocess(str, c, len);
	return (s);
}
