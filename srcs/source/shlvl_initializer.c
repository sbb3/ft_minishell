
#include "source_.h"

static bool	is_valid_as_shlvl_value__all_numeric(char *str)
{
	while (*str)
	{
		if (! ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

static void	join_key_value_to_set_to_envs(char *key, char *value, char **envs)
{
	char	*str;
	char	*temp_str;

	temp_str = ft_strjoin(key, "=");
	str = ft_strjoin(temp_str, value);
	free(temp_str);
	free(*envs);
	*envs = str;
}

static char	**get_varible_address_by_its_key(char *key, char **envs)
{
	int	i;

	i = -1;
	while (envs[++i])
	{
		if (ft_strcmp(envs[i], key) != '=')
			continue ;
		return (envs + i);
	}
	return (envs + i);
}

void	shlvl_initializer(t_env **envp, char **envs)
{
	t_env	*shlvl;
	char	**envs_shlvl;
	int		last_shlvl;

	envs_shlvl = get_varible_address_by_its_key("SHLVL", envs);
	shlvl = get_env_by_its_key(*envp, "SHLVL");
	if (shlvl == NULL)
	{
		env_add_back_to_envs(envp, new_env("SHLVL", "1"));
		join_key_value_to_set_to_envs("SHLVL", "1", envs_shlvl);
	}
	else if (is_valid_as_shlvl_value__all_numeric(shlvl->value))
	{
		last_shlvl = atoi(shlvl->value);
		free(shlvl->value);
		shlvl->value = ft_itoa(last_shlvl + 1);
		join_key_value_to_set_to_envs("SHLVL", shlvl->value, envs_shlvl);
	}
	else
	{
		free(shlvl->value);
		shlvl->value = ft_strdup("1");
		join_key_value_to_set_to_envs("SHLVL", "1", envs_shlvl);
	}
}
