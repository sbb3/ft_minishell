
#include "parser.h"

void	phaseone_helper(t_shell *data, int *k, int type1, int type2)
{
	int	i;

	i = (*k);
	if (type1 || type2)
	{
		data->tkns_recognition[i] = type1;
		data->tkns_recognition[++i] = type2;
		(*k) = i;
	}
	else
		data->tkns_recognition[i] = COMMAND;
}

void	phaseone(t_shell *data)
{
	int	k;
	int	i;

	k = 0;
	i = -1;
	while (++i < data->tokens_len)
	{
		if (!ft_strcmp(data->tokens[i], "<"))
			phaseone_helper(data, &i, LESS, INFILE);
		else if (!ft_strcmp(data->tokens[i], ">"))
			phaseone_helper(data, &i, GREATER, OUTFILE);
		else if (!ft_strcmp(data->tokens[i], "<<"))
			phaseone_helper(data, &i, HEREDOC, DELIMITER);
		else if (!ft_strcmp(data->tokens[i], ">>"))
			phaseone_helper(data, &i, APPEND, OUTFILE_APPEND);
		else
		{
			if (!k)
			{
				phaseone_helper(data, &i, 0, 0);
				k = 1;
			}
		}
	}
}

void	phasezero(t_shell *data)
{
	int	i;

	i = -1;
	while (++i < data->tokens_len)
		data->tkns_recognition[i] = ARGS;
}

int	*token_recognition(t_shell *data)
{
	data->tkns_recognition = malloc(sizeof(int) * data->tokens_len);
	exit_if_null(data->tkns_recognition, "Allocation failed");
	phasezero(data);
	phaseone(data);
	return (data->tkns_recognition);
}
