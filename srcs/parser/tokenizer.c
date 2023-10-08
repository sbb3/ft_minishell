
#include "parser.h"

void	redirectionhelper(char *s, int *to)
{
	int	i;

	i = (*to);
	if (s[i + 1] == LREDIR || s[i + 1] == RREDIR)
		i = i + 2;
	else
		i++;
	(*to) = i;
}

char	*pipehelper(int *from, int *lastpos)
{
	int	i;

	i = (*from);
	i++;
	(*from) = i;
	(*lastpos) = i;
	return (NULL);
}

void	quoteshelper(char *s, int *pos, char c)
{
	char	k;
	int		i;
	int		dqstate;
	int		sqstate;

	if_c_else_k(&c, &k, &dqstate, &sqstate);
	i = (*pos);
	while (s[i])
	{
		if (s[i] == ' ' && !sqstate && !dqstate)
			break ;
		else if (s[i] == c)
			localhelper2(&dqstate, sqstate);
		else if (s[i] == k)
			localhelper3(&sqstate, dqstate);
		else if ((s[i] == LREDIR || s[i] == RREDIR || s[i] == PIPE) \
			&& !sqstate && !dqstate)
			break ;
		i++;
	}
	(*pos) = i;
}

static char	*goback_if_null(char *last_token)
{
	if (last_token)
		free(last_token);
	return (NULL);
}

char	*get_token(char *s, int *lastpos)
{
	char	*token;
	int		to;
	int		from;

	from = *lastpos;
	while (iswhitespace(s[from]))
		from++;
	if (s[from] == '|')
		if (!pipehelper(&from, lastpos))
			return (NULL);
	to = from;
	if (s[to] == LREDIR || s[to] == RREDIR)
		redirectionhelper(s, &to);
	else if (s[to] == DOUBLEQUOTE)
		quoteshelper(s, &to, DOUBLEQUOTE);
	else if ((from == to && s[to] == SINGLEQUOTE))
		quoteshelper(s, &to, SINGLEQUOTE);
	else
		gettoken_helper2(s, &to);
	token = ft_strcut_from_to(s, from, to);
	if (!gettoken_helper(token, to, lastpos))
		return (goback_if_null(token));
	return (token);
}
