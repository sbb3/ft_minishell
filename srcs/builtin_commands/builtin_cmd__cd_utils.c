
#include "builtin_commands.h"

bool	_cd__chdir_and_modify_env(char *dirname, t_env **envs, \
												t_env *pwd, t_env *old_pwd)
{
	char	buff[251];
	char	oldbuff[251];
	char	*cwd;
	char	*oldcwd;

	oldcwd = getcwd(oldbuff, 251);
	if (chdir(dirname) == 0)
	{
		cwd = getcwd(buff, 251);
		if (cwd)
			replace_or_add_env__value_key_(envs, pwd, "PWD", cwd);
		if (oldcwd)
			replace_or_add_env__value_key_(envs, old_pwd, "OLDPWD", oldcwd);
		return (true);
	}
	else
		custom_msg_then_perror(dirname);
	return (false);
}

bool	directory_exist_or_not(char *dirname, t_builtin_cmd_data *data)
{
	DIR		*dir;

	dir = opendir(dirname);
	if (dir)
		closedir(dir);
	else
	{
		data->ext_stts = 1;
		custom_msg_then_perror(dirname);
		return (false);
	}
	return (true);
}

static void	dir_checker__dash__(t_builtin_cmd_data *data)
{
	t_env	*oldpwd;

	oldpwd = get_env_by_its_key(*data->env, "OLDPWD");
	if (oldpwd)
	{
		if (directory_exist_or_not(oldpwd->value, data))
			ft_putendl_fd(oldpwd->value, data->outfd);
	}
	else
	{
		data->ext_stts = 1;
		put_custom_error("cd: ", "OLDPWD not set");
	}
}

static void	dir_checker__telda__(char *dirname, t_builtin_cmd_data *data)
{
	t_env	*home;

	home = get_env_by_its_key(*data->env, "HOME");
	if (home)
	{
		if (*home->value)
			dirname = ft_strjoin(home->value, dirname + 1);
		else
			dirname = ft_strdup(".");
		directory_exist_or_not(dirname, data);
		free(dirname);
	}
}

void	dir_checker_in_multi_parts(char *dirname, t_builtin_cmd_data *data)
{
	if (*dirname == '\0')
		return ;
	else if (*dirname == '-' && *(dirname + 1) == '\0')
	{
		dir_checker__dash__(data);
	}
	else if (*dirname == '~')
	{
		dir_checker__telda__(dirname, data);
	}
	else
		directory_exist_or_not(dirname, data);
}
