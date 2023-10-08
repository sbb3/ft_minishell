
#include "parser.h"

char	**tokenizer(char *s, int *start)
{
	char	**tokens;
	char	*token;
	size_t	tkns_len;
	size_t	current_size;

	current_size = INITIAL;
	tokens = malloc(sizeof(char *) * INITIAL);
	exit_if_null(tokens, "Allocation failed");
	token = get_token(s, start);
	tkns_len = 0;
	while (token)
	{
		if (tkns_len == current_size - 1)
		{
			current_size *= 2;
			tokens = ft_copy(tokens, current_size, tkns_len);
		}
		tokens[tkns_len] = ft_strdup(token);
		free(token);
		token = get_token(s, start);
		tkns_len++;
	}
	free(token);
	tokens[tkns_len] = NULL;
	return (tokens);
}

void	parser(t_shell *data)
{
	t_component	*newnode;
	int			i;
	int			j;

	alloc_init(data);
	i = -1;
	while (++i < data->parts_count)
	{
		data->tokens = tokenizer(data->prompt_input, &(data->start));
		data->tokens_len = count(data->tokens);
		data->tkns_recognition = token_recognition(data);
		j = -1;
		while (++j < data->tokens_len)
		{
			if (skip_redirection(data->tkns_recognition[j]))
				continue ;
			else
			{
				newnode = ft_lstnew(data->tokens[j], data->tkns_recognition[j]);
				ft_lstadd_back(&(data->separator)[i], newnode);
			}
		}
		reset_memory(data);
	}
	free(data->prompt_input);
}
