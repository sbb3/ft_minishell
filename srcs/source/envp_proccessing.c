
#include "source_.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	env->next = NULL;
	return (env);
}

void	env_add_back_to_envs(t_env **envs, t_env *new_env)
{
	t_env	*env;

	if (*envs == NULL)
	{
		*envs = new_env;
		return ;
	}
	env = *envs;
	while (env->next)
		env = env->next;
	env->next = new_env;
}

t_env	*get_env_by_its_key(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	replace_or_add_env__value_key_(t_env **envs, \
										t_env *env, char *key, char *value)
{
	if (env)
	{
		free(env->value);
		env->value = ft_strdup(value);
	}
	else
		env_add_back_to_envs(envs, new_env(key, value));
}
