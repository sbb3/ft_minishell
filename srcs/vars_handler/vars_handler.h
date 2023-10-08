
#ifndef VARS_HANDLER_H
# define VARS_HANDLER_H

# include "../source/source_.h"

# define FORBIDDEN_CHARS "\\;&|><"
# define QUOTES_OR_FORB_CHAR_ERROR "unclosed quote or invalid identifier"

enum e_str_types
{
	SINGLE_Q,
	DOUBLE_Q,
	SIMPLE_STR,
};

typedef struct s_v_h_data
{
	t_env	*env;
	int		exit_status;
	int		str_type;
	char	limiter;
	char	*end_str;
}	t_v_h_data;

bool	quotes_and_forbidden_chars_checker(t_shell *shell);
char	*ft_strjoin_with_char(char const *s, char c);
bool	valid_char_in_var_name(char c);
bool	valid_char_in_var_key(char c);
char	*get_var_name__key_(char *src);
char	*get_var_value_by_its_key(char *key, t_env *env);
char	*var_to_value_in__str__from_to__address_(char *start, \
												t_v_h_data *v_h_data);
char	*var_to_value_in_str(char *src, t_v_h_data *v_h_data);
void	strings_parser_and_vars_handler(t_shell *shell);

#endif
