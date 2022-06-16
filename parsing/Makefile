# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/28 06:09:35 by mkaruvan          #+#    #+#              #
#    Updated: 2022/06/16 09:46:55 by ayassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parsing.a

SRC = 	p_assign_1.c p_assign_2.c p_dollar.c \
		p_expand.c p_list_assign.c p_list_normal.c \
		p_normal.c p_quote.c p_utils_1.c p_utils_2.c \
		prompt.c p_redirection.c big_list.c \
		../execute_src/child.c ../execute_src/pipex_utils.c \
		../execute_src/pipex.c ../execute_src/redirection.c \
		../execute_src/redirection2.c ../execute_src/temp_list.c \
		../execute_src/here_doc.c

		

DIRS = ../libft

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

