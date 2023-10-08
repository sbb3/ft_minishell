
#include "parser.h"

int	pipes_count(char *input)
{
	int	i;
	int	count;
	int	dqstate;
	int	sqstate;

	dqstate = 0;
	sqstate = 0;
	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '"')
			localhelper2(&dqstate, sqstate);
		else if (input[i] == '\'')
			localhelper3(&sqstate, dqstate);
		else if (input[i] == '|' && !dqstate && !sqstate)
			count++;
		i++;
	}
	return (count);
}

void	alloc_init(t_shell *data)
{
	data->start = 0;
	data->parts_count = pipes_count(data->prompt_input) + 1;
	data->separator = malloc(sizeof(t_component *) * data->parts_count);
	exit_if_null(data->separator, "Allocation failed");
	set_null(data);
}

t_shell	*init(int ac, char *av[])
{
	t_shell	*shell;

	(void) ac;
	(void) av;
	shell = ft_calloc(1, sizeof(t_shell));
	exit_if_null(shell, "Allocation failed");
	return (shell);
}
