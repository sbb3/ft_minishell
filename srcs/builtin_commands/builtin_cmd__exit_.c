
#include "builtin_commands.h"

static bool	check_this_string_is_numerical(char *str)
{
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (false);
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (false);
		str++;
	}
	return (true);
}

static bool	check_this_arg_is_int(char *str, int res)
{
	while (ft_isspace(*str))
		str++;
	if (res == -1)
	{
		if (*str != '-')
			return (false);
	}
	else if (res == 0)
	{
		if (*str == '-' || *str == '+')
			str++;
		while (*str)
			if (*str++ != '0')
				return (false);
	}
	return (true);
}

static void	write_num_arg_required_error_then_exit_255(char *str)
{
	write(2, "exit: ", 6);
	put_custom_error(str, ": numeric argument required");
	exit(255);
}

void	builtin_cmd__exit_(t_builtin_cmd_data *data)
{
	int	result;

	data->ext_stts = 0;
	if (data->part_counts == 1)
		write(2, "exit\n", 5);
	if (data->args[0] == NULL)
		exit (0);
	if (check_this_string_is_numerical(data->args[0]) == false)
		write_num_arg_required_error_then_exit_255(data->args[0]);
	result = ft_atoi(data->args[0]);
	if (check_this_arg_is_int(data->args[0], result) == false)
		write_num_arg_required_error_then_exit_255(data->args[0]);
	if (data->args[1])
	{
		put_custom_error("exit: ", "too many arguments");
		data->ext_stts = 1;
		return ;
	}
	if (data->part_counts > 1)
		return ;
	exit (result);
}
