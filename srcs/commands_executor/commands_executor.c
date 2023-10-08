
#include "commands_executor.h"

static char	*get_path_env_from_envp(t_env *envp)
{
	while (envp)
	{
		if (ft_strcmp(envp->key, "PATH") == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

static void	wait_all_pids(t_shell *shell, int *pids, int builtin_ext_stts)
{
	int	index;
	int	exit_status;

	index = 0;
	while (index < shell->parts_count)
	{
		if (pids[index] > 0)
		{
			waitpid(pids[index], &exit_status, 0);
			if (WIFSIGNALED(exit_status))
				shell->exit_status = exit_status + 128;
			else
				shell->exit_status = WEXITSTATUS(exit_status);
		}
		else
			shell->exit_status = builtin_ext_stts;
		pids[index] = 0;
		index++;
	}
}

void	commands_executor(t_shell *shell)
{
	t_cmd_data	*cmd_data;
	int			index;
	int			*pids;

	cmd_data = ft_calloc(1, sizeof(t_cmd_data));
	pids = ft_calloc(shell->parts_count, sizeof(int));
	cmd_data->infd = 0;
	cmd_data->path_env = get_path_env_from_envp(shell->envp);
	cmd_data->pids = pids;
	cmd_data->envs = shell->envs;
	index = 0;
	while (index < shell->parts_count)
	{
		cmd_data->component = shell->separator[index];
		command_executor(cmd_data, shell, index);
		cmd_data->infd = cmd_data->pipefd;
		if (cmd_data->heredoc_exit_with_sg_c)
			break ;
		index++;
	}
	wait_all_pids(shell, pids, cmd_data->builtin_ext_stts);
	if (cmd_data->pipefd > 2)
		close(cmd_data->pipefd);
	free(pids);
	free(cmd_data);
}
