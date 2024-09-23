# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: merdal <merdal@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/28 12:50:20 by merdal            #+#    #+#              #
#    Updated: 2024/09/20 16:12:46 by merdal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -Llibft -lft -lreadline
NAME = 	minishell

SRCS =	minishell.c input.c input2.c handle_dollar.c \
		ft_init.c utils.c tokenize.c parser.c ft_check_args.c \
		build_in_cmd/ft_echo.c build_in_cmd/ft_cd.c \
		build_in_cmd/ft_pwd.c build_in_cmd/ft_exe.c build_in_cmd/ft_export.c build_in_cmd/ft_env.c \
		build_in_cmd/ft_unset.c set_fds.c


OBJS = $(SRCS:.c=.o)
RM = rm -f
LIBFT = libft/libft.a

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft > /dev/null
	@echo "\033[0;32mlibft compiled\033[0m"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) > /dev/null
	@echo "\033[0;32mminishell compiled\033[0m"

clean:
	@$(RM) $(OBJS)
	@make -C libft clean > /dev/null
	@echo "\033[0;32mObject files removed\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@make -C libft fclean > /dev/null
	@echo "\033[0;32mCleaned\033[0m"

re: fclean 
	@echo "---------------------"
	@$(MAKE) all

.PHONY: all clean fclean re