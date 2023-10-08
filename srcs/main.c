
#include "../incl/minishell.h"

static void	free_all_unneeded_data(t_shell *shell)
{
	t_component	*this_c;
	t_component	*next_c;
	int			index;

	index = 0;
	while (index < shell->parts_count)
	{
		this_c = shell->separator[index];
		while (this_c)
		{
			next_c = this_c->next;
			free(this_c->content);
			free(this_c);
			this_c = next_c;
		}
		index++;
	}
	free(shell->separator);
}

char	*prompt(void)
{
	char				*input;
	struct sigaction	ctrl_c;

	ctrl_c.sa_flags = SA_RESTART;
	while (1337)
	{
		ctrl_c.sa_handler = sig_hundler__ctrl_c__before_readline;
		sigaction(SIGINT, &ctrl_c, NULL);
		input = readline(BGRN "minishell-1.0" RESET "$ ");
		ctrl_c.sa_handler = sig_hundler__ctrl_c__after_readline;
		sigaction(SIGINT, &ctrl_c, NULL);
		if (input == NULL)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		break ;
	}
	return (input);
}

int	main(int ac, char *av[], char *envp[])
{
	t_shell				*shell;
	struct sigaction	ctrl_back_slash;

	ctrl_back_slash.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &ctrl_back_slash, NULL);
	shell = init(ac, av);
	envinit(shell, envp);
	while (1337)
	{
		shell->prompt_input = prompt();
		check_ctrl_c_and_reset_checker_value(shell);
		if (check(shell->prompt_input) == 0)
		{
			free(shell->prompt_input);
			shell->exit_status = 1;
			continue ;
		}
		parser(shell);
		strings_parser_and_vars_handler(shell);
		commands_executor(shell);
		free_all_unneeded_data(shell);
	}
	return (0);
}
