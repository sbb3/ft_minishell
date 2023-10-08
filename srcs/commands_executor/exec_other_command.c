#include "commands_executor.h"

static void	free_2d__char__pointer(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

static char	*get_first_exec_or_exist_cmd__full_path(char *cmd, char **paths)
{
	char	*cmd_full_path;
	char	*exist__cmd_full_path;
	char	*path_slash;

	exist__cmd_full_path = NULL;
	while (paths && *paths)
	{
		path_slash = ft_strjoin(*paths, "/");
		cmd_full_path = ft_strjoin(path_slash, cmd);
		free(path_slash);
		if (access(cmd_full_path, F_OK) == 0)
		{
			if (access(cmd_full_path, X_OK) == 0)
				return (cmd_full_path);
			else
			{
				free(exist__cmd_full_path);
				exist__cmd_full_path = cmd_full_path;
			}
		}
		else
			free(cmd_full_path);
		paths++;
	}
	return (exist__cmd_full_path);
}

static char	*get_cmd_full_path(char *path, char *cmd)
{
	char	*cmd_full_path;
	char	**paths;

	if (*cmd == '\0')
	{
		put_custom_error("", COMMAND_NOT_FOUND_ERROR);
		exit (127);
	}
	if (ft_strchr(cmd, '/'))
		return (cmd);
	paths = ft_split(path, ':');
	if (paths && *paths)
	{
		cmd_full_path = get_first_exec_or_exist_cmd__full_path(cmd, paths);
		free_2d__char__pointer(paths);
		if (cmd_full_path)
			return (cmd_full_path);
	}
	else
		free_2d__char__pointer(paths);
	put_custom_error(cmd, COMMAND_NOT_FOUND_ERROR);
	exit (127);
}

static void	execut_command(char *cmd_path, char **args, char **envs, int fds[2])
{
	if (dup2(fds[0], 0) < 0 || dup2(fds[1], 1) < 0)
	{
		custom_msg_then_perror(DUP2_ERROR);
		exit (1);
	}
	if (execve(cmd_path, args, envs) < 0)
	{
		custom_msg_then_perror(args[0]);
		exit(1);
	}
}

void	get_cmd_full_path_then_exec_it(t_cmd_data *cmd_data, int outfd)
{
	char	*cmd_full_path;
	char	**cmd_and_args;
	int		in_out_fds[2];

	in_out_fds[0] = cmd_data->infd;
	in_out_fds[1] = outfd;
	cmd_and_args = get_cmd_and_args__from_component_(cmd_data->component);
	if (*cmd_and_args == NULL)
		exit (0);
	cmd_full_path = get_cmd_full_path(cmd_data->path_env, cmd_and_args[0]);
	execut_command(cmd_full_path, cmd_and_args, cmd_data->envs, in_out_fds);
	exit(0);
}
