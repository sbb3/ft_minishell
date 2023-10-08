#include "commands_executor.h"

static bool	compare__key_value__with__varible_str__(t_env *env, char *varible)
{
	if (ft_strcmp(varible, env->key) != '=')
		return (false);
	if (ft_strcmp(ft_strchr(varible, '=') + 1, env->value))
		return (false);
	return (true);
}

static void	join_key_and_value_to_set_to_envs(t_env *env, char **envs)
{
	char	*str;
	char	*temp_str;

	temp_str = ft_strjoin(env->key, "=");
	str = ft_strjoin(temp_str, env->value);
	free(temp_str);
	free(*envs);
	*envs = str;
}

void	update_envs__only_changed_varibles__(t_shell *shell)
{
	t_env	*envp;
	char	**envs;

	envp = shell->envp;
	envs = shell->envs;
	while (envp)
	{
		if (*(envp->key))
		{
			if (compare__key_value__with__varible_str__(envp, *envs) == false)
				join_key_and_value_to_set_to_envs(envp, envs);
			envs++;
		}
		envp = envp->next;
	}
}

static void	free_all_envs_strings_(char **envs)
{
	int	i;

	i = 0;
	while (envs[i])
	{
		free(envs[i]);
		i++;
	}
	free(envs);
}

void	update_envs__all_from_scratch__(t_shell *shell, int len_envp)
{
	char	**new_envs;
	t_env	*envp;

	free_all_envs_strings_(shell->envs);
	new_envs = ft_calloc(len_envp + 1, sizeof(char *));
	check_if_null__malloc__exit_(new_envs, MALLOC_ERROR);
	shell->envs = new_envs;
	envp = shell->envp;
	while (envp)
	{
		if (*(envp->key))
		{
			join_key_and_value_to_set_to_envs(envp, new_envs);
			new_envs++;
		}
		envp = envp->next;
	}
}
