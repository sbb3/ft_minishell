
#include "../parser/parser.h"

int	count(char *s[])
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strcut_from_to(char *s, int from, int to)
{
	char	*buf;
	int		i;

	buf = (char *)malloc(sizeof(char) * (to - from) + 1);
	if (!buf)
		return (0);
	i = 0;
	while (from < to)
	{
		buf[i] = s[from];
		from++;
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

char	**ft_copy(char **tokens, size_t size, size_t tkns_len)
{
	char	**new;
	size_t	y;

	new = malloc(sizeof(char *) * size);
	exit_if_null(new, "Allocation failed");
	y = 0;
	while (y < tkns_len)
	{
		new[y] = ft_strdup(tokens[y]);
		y++;
	}
	ft_free(tokens, tkns_len);
	return (new);
}

int	gettoken_helper(char *token, int to, int *lastpos)
{
	if ((*token) == '\0')
	{
		if (ft_strlen(token) == to)
		{
			(*lastpos) = to;
			return (0);
		}
		else
		{
			(*lastpos) = to + 1;
			return (0);
		}
	}
	else
		(*lastpos) = to;
	return (1);
}

void	gettoken_helper2(char *token, int *end)
{
	int	to;

	to = (*end);
	while (token[to])
	{
		if (token[to] == DOUBLEQUOTE)
			quoteshelper(token, &to, DOUBLEQUOTE);
		if (token[to] == SINGLEQUOTE)
			quoteshelper(token, &to, SINGLEQUOTE);
		if (token[to] == ' ')
			break ;
		if (token[to] == LREDIR || token[to] == RREDIR || token[to] == PIPE)
			break ;
		to++;
	}
	(*end) = to;
}
