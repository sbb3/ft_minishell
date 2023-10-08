#include "commands_executor.h"

static void	ft_get_here_doc_with_gunl(char *limiter, int outfd)
{
	char	*line;

	while (1337)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, limiter) == 0)
			break ;
		write(outfd, line, ft_strlen(line));
		write(outfd, "\n", 1);
		free(line);
	}
	free(line);
	exit (0);
}

int	ft_get_here_doc(char *limiter)
{
	int		fd_pipe[2];
	pid_t	pid;
	int		exit_status;

	if (pipe(fd_pipe) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		ft_get_here_doc_with_gunl(limiter, fd_pipe[1]);
	}
	close(fd_pipe[1]);
	waitpid(pid, &exit_status, 0);
	if (WIFSIGNALED(exit_status))
	{
		close(fd_pipe[0]);
		return (-1);
	}
	return (fd_pipe[0]);
}
