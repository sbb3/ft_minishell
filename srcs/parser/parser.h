
#ifndef PARSER_H
# define PARSER_H

# include "../../incl/minishell.h"

# define INITIAL 200

// ERROR FUNCTIONS
int			syntax_error(char *s);
void		quit(char *s, int errornum);
void		exit_if_null(void *p, char *message);

// PARSING
void		parser(t_shell *data);
char		**tokenizer(char *s, int *start);
int			*token_recognition(t_shell *data);
char		*get_token(char *s, int *lastpos);
t_shell		*init(int ac, char *av[]);
void		alloc_init(t_shell *data);
void		envinit(t_shell *data, char *envp[]);
char		**ft_copy(char **tokens, size_t size, size_t tkns_len);

// CHECKIN'
int			check(char *input);
int			check_redir(char *s, int i, char c);
int			check_pipe(char *s, int i);
void		quotescheck(char c, int *dqstate, int *sqstate);
int			check_redirec(char *s, int i);
void		check_helper1(int *dq);
void		check_helper2(int *sq);
int			another_helper(int *count, int whitespace);

// UTILS FUNCTIONS 1
char		*ft_strcut_from_to(char *s, int from, int to);
t_component	*ft_lstnew(char *content, int tkn_type);
void		ft_lstadd_back(t_component **lst, t_component *new);
t_env		*lstinit(char *key, char *value);
void		pushback(t_env **head, t_env *new);

// UTILS FUNCTIONS 2
int			isprintable(int c);
int			count(char *s[]);
int			pipes_count(char *input);
int			quotes_count(char *s, int start, char c);
void		set_null(t_shell *data);
char		*getkey(char *s);
void		if_c_else_k(char *c, char *k, int *dqstate, int *sqstate);
int			iswhitespace(char c);
void		skipspaces(char *s, int *pos, int *space, int w);
void		reset_memory(t_shell *data);
void		ft_free(char **tokens, size_t tkns_len);

// HELPER FUNCTIONS
void		phasezero(t_shell *data);
void		phaseone(t_shell *data);
void		quoteshelper(char *s, int *to, char c);
char		*pipehelper(int *from, int *lastpos);
char		*shlvl_helper(char *value);
int			check_redir_helper(char *s, int i);
int			gettoken_helper(char *token, int to, int *lastpos);
void		gettoken_helper2(char *token, int *end);
void		phaseone_helper(t_shell *data, int *k, int type1, int type2);
void		localhelper2(int *dqstate, int sqstate);
void		localhelper3(int *sqstate, int dqstate);
void		redirectionhelper(char *s, int *to);
int			skip_redirection(int token_type);

#endif
