
#include "../parser/parser.h"

int	iswhitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' \
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void	if_c_else_k(char *c, char *k, int *dqstate, int *sqstate)
{
	(*dqstate) = 0;
	(*sqstate) = 0;
	if (*c == '"')
		*k = '\'';
	else if (*c == '\'')
		*k = '"';
}

int	skip_redirection(int token_type)
{
	if (token_type == LESS || token_type == HEREDOC || \
		token_type == GREATER || token_type == APPEND)
		return (1);
	return (0);
}

void	set_null(t_shell *data)
{
	int	i;

	i = -1;
	while (++i < data->parts_count)
		(data->separator)[i] = NULL;
}

void	reset_memory(t_shell *data)
{
	int	i;

	if (data->tokens)
	{
		i = -1;
		while (++i < data->tokens_len)
			free(data->tokens[i]);
		free(data->tokens);
	}
	if (data->tkns_recognition)
	{
		free(data->tkns_recognition);
	}
}
