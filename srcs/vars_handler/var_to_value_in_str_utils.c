
#include "vars_handler.h"

char	*ft_strjoin_with_char(char const *s, char c)
{
	char	*str;
	char	*save_str;

	if (! s)
		s = "";
	str = malloc(ft_strlen(s) + 2);
	if (! str)
		return (NULL);
	save_str = str;
	while (*s)
		*str++ = *s++;
	*str++ = c;
	*str = '\0';
	return (save_str);
}

bool	valid_char_in_var_key(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

bool	valid_char_in_var_name(char c)
{
	if (c == '?')
		return (true);
	if (valid_char_in_var_key(c))
		return (true);
	return (false);
}

char	*get_var_name__key_(char *begin_var_key)
{
	char	*str;
	char	*end_var_key;

	end_var_key = begin_var_key;
	while (valid_char_in_var_key(*end_var_key))
		end_var_key++;
	str = strdup_from_to__address_(begin_var_key, end_var_key);
	return (str);
}

char	*get_var_value_by_its_key(char *key, t_env *env)
{
	if (! *key)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
