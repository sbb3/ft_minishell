
CC = cc

# RDFLAGS= -lreadline -L/goinfre/$(USER)/.brew/opt/readline/lib
RDFLAGS= -lreadline -L/Volumes/SBB3/homebrew/opt/readline/lib

CFLAGS = -I./incl/ -Wall -Wextra -Werror  # -g3 -fsanitize=address 

RM = rm -rf

COLOUR_BLUE=\033[0;35m

COLOUR_END=\033[0m

SRCS = srcs/main.c srcs/signal_hundler.c \
		srcs/parser/alloc_init.c srcs/parser/parser.c  srcs/parser/check.c \
		srcs/parser/token_recognition.c srcs/parser/tokenizer.c \
		srcs/parser/envinit.c srcs/parser/error_quit.c srcs/utils_functions/utils.c \
		srcs/utils_functions/utils2.c srcs/utils_functions/utils3.c \
		srcs/utils_functions/utils4.c srcs/utils_functions/lst_utils.c 

SOURCE = srcs/source/calloc.c srcs/source/char_genre.c srcs/source/itoa_and_atoi.c \
		srcs/source/envp_proccessing.c srcs/source/mem_str_comparing.c \
		srcs/source/put_custom_error.c srcs/source/split.c srcs/source/string_proccessing.c \
		srcs/source/shlvl_initializer.c srcs/source/linked_lists.c 


BUILT_CMD = srcs/builtin_commands/builtin_cmd__unset_.c srcs/builtin_commands/builtin_cmd__echo_.c \
			srcs/builtin_commands/builtin_cmd__env_.c srcs/builtin_commands/builtin_cmd__exit_.c \
			srcs/builtin_commands/builtin_cmd__export_.c srcs/builtin_commands/builtin_cmd__pwd_.c \
			srcs/builtin_commands/builtin_cmd__cd_.c srcs/builtin_commands/builtin_cmd__cd_utils.c \
			srcs/builtin_commands/utils_for_unset_and_export.c 

CMD_EXEC = srcs/commands_executor/cmds_executor.c srcs/commands_executor/cmds_executor_utils.c \
			srcs/commands_executor/commands_executor.c srcs/commands_executor/exec_builtin_command.c \
			srcs/commands_executor/exec_other_command.c srcs/commands_executor/get_here_doc.c \
			srcs/commands_executor/input_and_output_fds_minner.c srcs/commands_executor/envs_updater.c \
			srcs/commands_executor/envs_updater_utils.c 

VARS_HANDLER = srcs/vars_handler/quotes_and_forbidden_chars_checker.c \
				srcs/vars_handler/strings_parser_and_vars_handler.c \
				srcs/vars_handler/var_to_value_in_str.c \
				srcs/vars_handler/var_to_value_in_str_utils.c 


OBJS = $(SRCS:%.c=%.o)
O_SOURCE = $(SOURCE:%.c=%.o)
O_BUILT_CMD = $(BUILT_CMD:%.c=%.o)
O_CMD_EXEC = $(CMD_EXEC:%.c=%.o)
O_VAR_HANDLER = $(VARS_HANDLER:%.c=%.o)

NAME = minishell

$(VERBOSE).SILENT:

all: $(NAME)

$(NAME): $(OBJS) $(O_SOURCE) $(O_BUILT_CMD) $(O_CMD_EXEC) $(O_VAR_HANDLER)
	@$(CC) $(RDFLAGS) $(OBJS) $(O_SOURCE) $(O_BUILT_CMD) $(O_CMD_EXEC) $(O_VAR_HANDLER) -o $(NAME)
	@echo "👉 $(COLOUR_BLUE)COMPILING DONE$(COLOUR_END) 👈"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS) $(O_SOURCE) $(O_BUILT_CMD) $(O_CMD_EXEC) $(O_VAR_HANDLER)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
