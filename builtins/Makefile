# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/05 17:25:55 by mkaruvan          #+#    #+#              #
#    Updated: 2022/06/05 17:25:56 by mkaruvan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = builtins.a

SRC = 	ft_cd.c ft_echo.c ft_env.c ft_exit.c \
		ft_export.c ft_pwd.c ft_unset.c

CC = gcc

CFLAGS = -g3 -Werror -Wall -Wextra


OBJS = $(SRC:.c=.o)


all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I../libft -I../ft_printf -c $^ -o $@

$(NAME): $(OBJS)
	ar cr  $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean libft