#include "commands_executor.h"

static int	envp_len_without_empty_keys(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		if (*env->key)
			len++;
		env = env->next;
	}
	return (len);
}

void	envs_updater(char *cmd, t_shell *shell)
{
	int		len_envs;
	int		len_envp;
	char	**envs;

	if (shell->parts_count != 1)
		return ;
	if (ft_strcmp(cmd, "cd") && ft_strcmp(cmd, "export") && \
									ft_strcmp(cmd, "unset"))
		return ;
	envs = shell->envs;
	len_envs = 0;
	while (envs[len_envs])
		len_envs++;
	len_envp = envp_len_without_empty_keys(shell->envp);
	if (len_envs == len_envp)
		update_envs__only_changed_varibles__(shell);
	else
		update_envs__all_from_scratch__(shell, len_envp);
}
