
#include "source_.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (! s)
		return ;
	while (*s)
		write(fd, s++, 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (! s)
		return ;
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

void	put_custom_error(char *str_error1, char *str_error2)
{
	ft_putstr_fd(BRED SHELL_NAME RESET, 2);
	if (str_error1)
		ft_putstr_fd(str_error1, 2);
	if (str_error2)
		ft_putstr_fd(str_error2, 2);
	write(2, "\n", 1);
}

void	custom_msg_then_perror(char *str)
{
	ft_putstr_fd(BRED SHELL_NAME RESET, 2);
	perror(str);
}

void	check_if_null__malloc__exit_(void *ptr, char *str)
{
	if (ptr == NULL)
	{
		ft_putstr_fd(BRED SHELL_NAME RESET, 2);
		perror(str);
		exit (1);
	}
}
