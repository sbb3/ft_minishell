
#include "builtin_commands.h"

static void	free_this_env_node__key_value_node__(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

static void	delete_this_env_varible(t_env **envs, char *key)
{
	t_env	*env;
	t_env	*last_env;

	if (*envs == NULL)
		return ;
	env = *envs;
	if (ft_strcmp(env->key, key) == 0)
	{
		*envs = env->next;
		free_this_env_node__key_value_node__(env);
		return ;
	}
	last_env = env;
	env = env->next;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			last_env->next = env->next;
			free_this_env_node__key_value_node__(env);
			return ;
		}
		last_env = env;
		env = env->next;
	}
}

void	builtin_cmd__unset_(t_builtin_cmd_data *data)
{
	int		index;

	data->ext_stts = 0;
	if (data->args[0] == NULL)
	{
		data->ext_stts = 1;
		put_custom_error("unset: ", "not enough arguments");
		return ;
	}
	index = 0;
	while (data->args[index])
	{
		if (is_this_key_valid_as_var_key(data->args[index]))
		{
			if (data->part_counts == 1)
				delete_this_env_varible(data->env, data->args[index]);
		}
		else
		{
			data->ext_stts = 1;
			put_not_a_valid_identifier_error("unset", data->args[index]);
		}
		index++;
	}
}
