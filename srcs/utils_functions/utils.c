
#include "../parser/parser.h"

int	isprintable(int c)
{
	if (c > 32 && c <= 126)
		return (1);
	return (0);
}

void	ft_free(char **tokens, size_t tkns_len)
{
	size_t	i;

	i = 0;
	while (i < tkns_len)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	skipspaces(char *s, int *pos, int *space, int w)
{
	int	i;
	int	whitespace;

	i = (*pos);
	whitespace = (*space);
	if (w)
	{
		while (iswhitespace(s[i]))
		{
			whitespace++;
			i++;
		}
	}
	else
	{
		while (iswhitespace(s[i]) || s[i] == '<' || s[i] == '>')
		{
			whitespace++;
			i++;
		}
	}
	(*pos) = i;
	(*space) = whitespace;
}
