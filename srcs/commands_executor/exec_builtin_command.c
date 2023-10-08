#include "commands_executor.h"

static t_builtin_cmd_data	*set_init_data_struct(t_shell *shell, int outfd)
{
	t_builtin_cmd_data	*data;

	data = ft_calloc(1, sizeof(t_builtin_cmd_data));
	check_if_null__malloc__exit_(data, MALLOC_ERROR);
	data->env = &shell->envp;
	data->outfd = outfd;
	data->part_counts = shell->parts_count;
	return (data);
}

static void	builtin_commands_executor(char *cmd, t_builtin_cmd_data *data)
{
	if (ft_strcmp(cmd, "echo") == 0)
		builtin_cmd__echo_(data);
	else if (ft_strcmp(cmd, "cd") == 0)
		builtin_cmd__cd_(data);
	else if (ft_strcmp(cmd, "pwd") == 0)
		builtin_cmd__pwd_(data);
	else if (ft_strcmp(cmd, "export") == 0)
		builtin_cmd__export_(data);
	else if (ft_strcmp(cmd, "unset") == 0)
		builtin_cmd__unset_(data);
	else if (ft_strcmp(cmd, "env") == 0)
		builtin_cmd__env_(data);
	else if (ft_strcmp(cmd, "exit") == 0)
		builtin_cmd__exit_(data);
}

static void	free_data__close_fds(void *data, void *args, int fd1, int fd2)
{
	free(args);
	free(data);
	if (fd1 > 2)
		close(fd1);
	if (fd2 > 2)
		close(fd2);
}

void	exec_builtin_command(t_cmd_data *cmd_data, t_shell *shell, int outfd)
{
	char				**cmd_and_args;
	int					input_fd;
	int					output_fd;
	t_builtin_cmd_data	*builtin_data;

	cmd_data->builtin_ext_stts = 0;
	if (set__in_out__files_fds(&input_fd, &output_fd, cmd_data) == false)
	{
		cmd_data->builtin_ext_stts = 1;
		return ;
	}
	if (output_fd > 2)
		outfd = output_fd;
	cmd_and_args = get_cmd_and_args__from_component_(cmd_data->component);
	if (cmd_and_args[0] == NULL)
		return ;
	builtin_data = set_init_data_struct(shell, outfd);
	builtin_data->args = cmd_and_args + 1;
	builtin_commands_executor(cmd_and_args[0], builtin_data);
	cmd_data->builtin_ext_stts = builtin_data->ext_stts;
	envs_updater(cmd_and_args[0], shell);
	free_data__close_fds(builtin_data, cmd_and_args, input_fd, output_fd);
}
