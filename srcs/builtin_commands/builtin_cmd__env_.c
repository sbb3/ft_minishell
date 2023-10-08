
#include "builtin_commands.h"

void	builtin_cmd__env_(t_builtin_cmd_data *data)
{
	t_env	*env;

	env = *data->env;
	if (data->args[0])
	{
		put_custom_error("env: ", "too many arguments");
		data->ext_stts = 1;
		return ;
	}
	while (env)
	{
		if (*env->key != '\0')
		{
			ft_putstr_fd(env->key, data->outfd);
			write(data->outfd, "=", 1);
			ft_putstr_fd(env->value, data->outfd);
			write(data->outfd, "\n", 1);
		}
		env = env->next;
	}
	data->ext_stts = 0;
}
