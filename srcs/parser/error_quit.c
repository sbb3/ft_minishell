
#include "parser.h"

int	syntax_error(char *s)
{
	put_custom_error(s, NULL);
	return (0);
}

void	exit_if_null(void *p, char *message)
{
	if (!p)
	{
		put_custom_error(message, NULL);
		exit(EXIT_FAILURE);
	}
}

void	quit(char *s, int errornum)
{
	put_custom_error(s, NULL);
	exit(errornum);
}
