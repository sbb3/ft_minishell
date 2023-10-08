
#include "builtin_commands.h"

static void	_cd__dirname_as_dash(t_builtin_cmd_data *data, \
									t_env *pwd, t_env *old_pwd)
{
	if (old_pwd)
	{
		if (_cd__chdir_and_modify_env(old_pwd->value, data->env, pwd, old_pwd))
		{
			if (pwd == NULL)
				pwd = get_env_by_its_key(*data->env, "PWD");
			ft_putendl_fd(pwd->value, data->outfd);
		}
		else
			data->ext_stts = 1;
	}
	else
	{
		data->ext_stts = 1;
		put_custom_error("cd: ", "OLDPWD not set");
	}
}

static void	_cd__dirname_as_telda(char *dirname, t_builtin_cmd_data *data, \
										t_env *pwd, t_env *old_pwd)
{
	t_env	*home;

	home = get_env_by_its_key(*data->env, "HOME");
	if (home)
	{
		if (*home->value == '\0' && *(dirname + 1) == '\0')
			dirname = ft_strdup(".");
		else
			dirname = ft_strjoin(home->value, dirname + 1);
	}
	else
		dirname = ft_strdup(".");
	if (! _cd__chdir_and_modify_env(dirname, data->env, pwd, old_pwd))
		data->ext_stts = 1;
	free(dirname);
}

static void	_cd__dirname_parser(char *dirname, t_builtin_cmd_data *data)
{
	t_env	*pwd;
	t_env	*old_pwd;

	pwd = get_env_by_its_key(*data->env, "PWD");
	old_pwd = get_env_by_its_key(*data->env, "OLDPWD");
	if (*dirname == '\0')
		dirname = ".";
	else if (*dirname == '-' && *(dirname + 1) == '\0')
	{
		_cd__dirname_as_dash(data, pwd, old_pwd);
		return ;
	}
	else if (*dirname == '~')
	{
		_cd__dirname_as_telda(dirname, data, pwd, old_pwd);
		return ;
	}
	if (! _cd__chdir_and_modify_env(dirname, data->env, pwd, old_pwd))
		data->ext_stts = 1;
}

void	builtin_cmd__cd_(t_builtin_cmd_data *data)
{
	data->ext_stts = 0;
	if (data->args[0] == NULL)
	{
		if (data->part_counts == 1)
			_cd__dirname_parser("~", data);
	}
	else if (data->args[1])
	{
		data->ext_stts = 1;
		put_custom_error("cd: ", "too many arguments");
	}
	else if (data->part_counts == 1)
		_cd__dirname_parser(data->args[0], data);
	else
		dir_checker_in_multi_parts(data->args[0], data);
}
