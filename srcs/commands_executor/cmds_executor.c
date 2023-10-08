
#include "commands_executor.h"

void	exec_other_command(t_cmd_data *cmd_data, int id, int outfd)
{
	int		input_fd;
	int		output_fd;

	if (set__in_out__files_fds(&input_fd, &output_fd, cmd_data) == false)
	{
		cmd_data->builtin_ext_stts = 1;
		return ;
	}
	cmd_data->pids[id] = fork();
	if (cmd_data->pids[id] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (input_fd > 2)
			cmd_data->infd = input_fd;
		if (output_fd > 2)
			outfd = output_fd;
		close(cmd_data->pipefd);
		get_cmd_full_path_then_exec_it(cmd_data, outfd);
		exit (0);
	}
	if (input_fd > 2)
		close (input_fd);
	if (output_fd > 2)
		close (output_fd);
}

void	command_executor(t_cmd_data *cmd_data, t_shell *shell, int id)
{
	int	pipe_fds[2];
	int	outfd;

	if (pipe(pipe_fds) < 0)
		check_if_null__malloc__exit_(NULL, PIPE_ERROR);
	cmd_data->pipefd = pipe_fds[0];
	if (id < shell->parts_count - 1)
		outfd = pipe_fds[1];
	else
		outfd = 1;
	if (this_is_builtin_command(cmd_data->component))
		exec_builtin_command(cmd_data, shell, outfd);
	else
		exec_other_command(cmd_data, id, outfd);
	if (cmd_data->infd > 2)
		close(cmd_data->infd);
	close(pipe_fds[1]);
}
