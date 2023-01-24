NAME = minishell

SRC = main.c ft_split.c utility.c ft_strlen.c utility2.c redirUtils.c \
		builtin.c ft_strdup.c echo.c ft_itoa.c check.c pwd.c env.c wildcard.c\
			cd.c ft_strrchr.c free.c utility3.c pipes.c exp.c heredoc.c signal.c \
				logical_op.c parentheses.c init.c exec.c subshell.c

FLAG = -Wall -Wextra -Werror -g -lreadline -L/Users/$(USER)/.brew/opt/readline/lib 

$(NAME): 
		gcc $(FLAG) $(SRC) -o $(NAME)

clean:
		rm -f $(NAME)

fclean: clean

all: $(NAME)

re: fclean all