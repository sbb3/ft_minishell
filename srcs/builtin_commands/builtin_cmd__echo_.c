
#include "builtin_commands.h"

static void	set__new_line__args_as_null(char **args)
{
	char	*str;

	while (*args)
	{
		str = *args;
		if (*str++ == '-')
		{
			if (*str == '\0')
				return ;
			while (*str)
			{
				if (*str != 'n')
					return ;
				str++;
			}
			*args = NULL;
		}
		else
			return ;
		args++;
	}
}

static void	print_all_strings(char **args, int len, int outfd)
{
	int	index;

	index = 0;
	while (index < len)
	{
		if (args[index])
		{
			write(outfd, args[index], ft_strlen(args[index]));
			if (index < len - 1)
				write(outfd, " ", 1);
			else if (args[0])
				write(outfd, "\n", 1);
		}
		index++;
	}
}

void	builtin_cmd__echo_(t_builtin_cmd_data *data)
{
	int	len;

	data->ext_stts = 0;
	if (data->args[0] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	len = 0;
	while (data->args[len])
		len++;
	set__new_line__args_as_null(data->args);
	print_all_strings(data->args, len, data->outfd);
}
