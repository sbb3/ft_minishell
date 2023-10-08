
#include "builtin_commands.h"

void	builtin_cmd__pwd_(t_builtin_cmd_data *data)
{
	char	buff[251];
	char	*cwd;

	data->ext_stts = 0;
	cwd = getcwd(buff, 251);
	if (cwd == NULL)
	{
		custom_msg_then_perror("pwd");
		return ;
	}
	ft_putendl_fd(buff, data->outfd);
}
