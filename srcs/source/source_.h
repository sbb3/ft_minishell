
#ifndef SOURCE__H
# define SOURCE__H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/types.h>
# include <dirent.h>

# include "../../incl/source.h"

# define SHELL_NAME "minishell-1.0: "

# define MALLOC_ERROR "error malloc()"
# define PIPE_ERROR "error pipe()"
# define FORK_ERROR "error fork()"
# define WAITPID_ERROR "error waitpid()"
# define DUP2_ERROR "error dup2()"
# define READ_ERROR "error read()"
# define WRITE_ERROR "error write()"
# define OPEN_ERROR "error open()"
# define READ_OR_WRITE_ERROR "error read()/write()"
# define COMMAND_NOT_FOUND_ERROR ": command not found"

void	custom_msg_then_perror(char *str);
void	put_custom_error(char *str_error1, char *str_error2);
int		list_component_size(t_component *lst);
char	*strdup_from_to__address_(char *start, char *end);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
int		ft_isspace(char c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
char	*ft_itoa(int num);
char	**ft_split(const char *str, char c);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *string);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *s);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	check_if_null__malloc__exit_(void *ptr, char *str);
t_env	*new_env(char *key, char *value);
void	env_add_back_to_envs(t_env **envs, t_env *new_env);
void	replace_or_add_env__value_key_(t_env **envs, \
										t_env *env, char *key, char *value);
t_env	*get_env_by_its_key(t_env *env, char *key);
void	shlvl_initializer(t_env **envp, char **envs);

#endif
