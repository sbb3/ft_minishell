
#include "source_.h"

int	ft_strlen(const char *s)
{
	size_t	l;

	if (! s)
		return (0);
	l = 0;
	while (*s++)
		l++;
	return (l);
}

char	*ft_strchr(const char *str, int c)
{
	char	cc;

	if (! str)
		return (NULL);
	cc = (char)c;
	while (*str && *str != cc)
		str++;
	if (*str == cc)
		return ((char *)str);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	char	*save_r;

	if (! s1 || ! s2)
		return (NULL);
	r = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (! r)
		return (r);
	save_r = r;
	while (*s1)
		*r++ = *s1++;
	while (*s2)
		*r++ = *s2++;
	*r = 0;
	return (save_r);
}

char	*ft_strdup(const char *string)
{
	char	*r;
	char	*save_r;
	size_t	l;

	l = ft_strlen(string);
	r = (char *)malloc(l + 1);
	if (! r)
		return (NULL);
	save_r = r;
	while (*string)
		*r++ = *string++;
	*r = 0;
	return (save_r);
}

char	*strdup_from_to__address_(char *start, char *end)
{
	char	*str;
	char	*ptr;
	size_t	len;

	len = 0;
	if (! start || ! end || start > end)
		return (NULL);
	ptr = start;
	while (ptr++ < end)
		len++;
	str = (char *)malloc(len + 1);
	ptr = str;
	while (start < end)
		*str++ = *start++;
	*str = '\0';
	return (ptr);
}
