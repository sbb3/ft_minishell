
#include "commands_executor.h"

char	**get_cmd_and_args__from_component_(t_component *component)
{
	int		index;
	char	**cmd_and_args;

	index = list_component_size(component);
	cmd_and_args = (char **)ft_calloc(index + 1, sizeof(char *));
	index = 0;
	while (component)
	{
		if (component->type == ARGS || component->type == COMMAND)
		{
			cmd_and_args[index] = component->content;
			index++;
		}
		component = component->next;
	}
	return (cmd_and_args);
}

static char	*this_is_builtin_command__cmd_getter__(t_component *component)
{
	while (component)
	{
		if (component->type == COMMAND)
			return (component->content);
		component = component->next;
	}
	return (NULL);
}

bool	this_is_builtin_command(t_component *component)
{
	char	*str;
	char	*builtin_cmds[8];
	int		index;

	builtin_cmds[0] = "echo";
	builtin_cmds[1] = "cd";
	builtin_cmds[2] = "pwd";
	builtin_cmds[3] = "export";
	builtin_cmds[4] = "unset";
	builtin_cmds[5] = "env";
	builtin_cmds[6] = "exit";
	builtin_cmds[7] = NULL;
	str = this_is_builtin_command__cmd_getter__(component);
	if (str == NULL)
		return (false);
	index = 0;
	while (builtin_cmds[index])
	{
		if (ft_strcmp(str, builtin_cmds[index]) == 0)
			return (true);
		index++;
	}
	return (false);
}
