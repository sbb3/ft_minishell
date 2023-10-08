
#include "source_.h"

int	ft_isspace(char c)
{
	if (c == 32)
		return (1);
	if (c > 8 && c < 14)
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if (c > 64 && c < 91)
		return (1);
	if (c > 96 && c < 123)
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
