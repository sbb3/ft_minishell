
#include "vars_handler.h"

static char	*get__address__until_limiter(char *str, char limiter)
{
	while (*str)
	{
		if (limiter == '\0' && (*str == '"' || *str == '\''))
			return (str);
		if (*str == limiter)
			return (str);
		str++;
	}
	return (str);
}

static void	set_limiter_and_str_type(char **str, t_v_h_data *v_h_data)
{
	if (**str == '"')
	{
		v_h_data->str_type = DOUBLE_Q;
		v_h_data->limiter = '"';
		*str = *str + 1;
	}
	else if (**str == '\'')
	{
		v_h_data->str_type = SINGLE_Q;
		v_h_data->limiter = '\'';
		*str = *str + 1;
	}
	else
	{
		v_h_data->str_type = SIMPLE_STR;
		v_h_data->limiter = '\0';
	}
}

static char	*quotes_and_vars_hundler(char *str, t_v_h_data *v_h_data)
{
	char	*final_str;
	char	*temp_final_str;
	char	*temp_ptr;

	final_str = ft_strdup("");
	while (*str)
	{
		set_limiter_and_str_type(&str, v_h_data);
		v_h_data->end_str = get__address__until_limiter(str, v_h_data->limiter);
		if (v_h_data->str_type == SINGLE_Q)
			temp_ptr = strdup_from_to__address_(str, v_h_data->end_str);
		else
			temp_ptr = var_to_value_in__str__from_to__address_(str, v_h_data);
		temp_final_str = ft_strjoin(final_str, temp_ptr);
		free(temp_ptr);
		free(final_str);
		final_str = temp_final_str;
		str = v_h_data->end_str;
		if (v_h_data->limiter)
			str++;
	}
	return (final_str);
}

static void	vars_handler__in_components_(t_component *component, \
											t_v_h_data *v_h_data)
{
	char	*str;

	while (component)
	{
		v_h_data->end_str = "";
		v_h_data->str_type = SIMPLE_STR;
		if (ft_strchr(component->content, '"') || \
										ft_strchr(component->content, '\''))
			str = quotes_and_vars_hundler(component->content, v_h_data);
		else
			str = var_to_value_in_str(component->content, v_h_data);
		free(component->content);
		component->content = str;
		component = component->next;
	}
}

void	strings_parser_and_vars_handler(t_shell *shell)
{
	t_component	*component;
	t_v_h_data	*v_h_data;
	int			index;

	v_h_data = ft_calloc(1, sizeof(t_v_h_data));
	check_if_null__malloc__exit_(v_h_data, MALLOC_ERROR);
	v_h_data->env = shell->envp;
	v_h_data->exit_status = shell->exit_status;
	index = 0;
	while (index < shell->parts_count)
	{
		component = shell->separator[index];
		vars_handler__in_components_(component, v_h_data);
		index++;
	}
	free(v_h_data);
}
