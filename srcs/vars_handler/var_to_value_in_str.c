
#include "vars_handler.h"

static char	*find_ext_stts__replace_it(char **src, char *str, int exit_status)
{
	char	*temp_str;
	char	*str_exit_status;

	str_exit_status = ft_itoa(exit_status);
	temp_str = ft_strjoin(str, str_exit_status);
	free(str_exit_status);
	*src = *src + 1;
	return (temp_str);
}

char	*find_var_and_replace_it(char **src, char *str, t_v_h_data *v_h_data)
{
	char	*var_key;
	char	*var_value;

	if (ft_isdigit(**src))
	{
		*src = *src + 1;
		return (NULL);
	}
	if (**src == '?')
		return (find_ext_stts__replace_it(src, str, v_h_data->exit_status));
	var_key = get_var_name__key_(*src);
	*src = *src + ft_strlen(var_key);
	var_value = get_var_value_by_its_key(var_key, v_h_data->env);
	free(var_key);
	return (ft_strjoin(str, var_value));
}

char	*strdup_until_next_var_sign(char **src, char *str, t_v_h_data *v_h_data)
{
	char	*next_sign;
	char	*result;
	char	*temp;

	if (**src == '$' && *(*src + 1) == '\0')
	{
		*src = *src + 1;
		if (v_h_data->str_type == SIMPLE_STR && *v_h_data->end_str != '\0')
			return (ft_strdup(str));
		else
			return (ft_strjoin(str, "$"));
	}
	next_sign = *src + 1;
	while (*next_sign)
	{
		if (*next_sign == '$' && (valid_char_in_var_name(*(next_sign + 1)) \
														|| !*(next_sign + 1)))
			break ;
		next_sign++;
	}
	temp = strdup_from_to__address_(*src, next_sign);
	result = ft_strjoin(str, temp);
	free(temp);
	*src = next_sign;
	return (result);
}

char	*var_to_value_in_str(char *src, t_v_h_data *v_h_data)
{
	char	*temp_str;
	char	*str;

	str = ft_strdup("");
	while (*src)
	{
		if (*src == '$' && valid_char_in_var_name(*(src + 1)))
		{
			src++;
			temp_str = find_var_and_replace_it(&src, str, v_h_data);
			if (temp_str)
			{
				free(str);
				str = temp_str;
			}
		}
		else
		{
			temp_str = strdup_until_next_var_sign(&src, str, v_h_data);
			free(str);
			str = temp_str;
		}
	}
	return (str);
}

char	*var_to_value_in__str__from_to__address_(char *start, \
												t_v_h_data *v_h_data)
{
	char	*str;
	char	*vars_in_str;

	str = strdup_from_to__address_(start, v_h_data->end_str);
	if (! str)
		return (NULL);
	vars_in_str = var_to_value_in_str(str, v_h_data);
	free(str);
	return (vars_in_str);
}
