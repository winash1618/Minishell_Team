# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 08:40:39 by ayassin           #+#    #+#              #
#    Updated: 2022/05/25 14:58:29 by ayassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

Headers = minishell.h

SRC = minishell.c pipex.c

SUBDIRS = libft ft_printf

OBJS = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

.c.o:
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFLAGS) -Ilibft -Ift_printf -c $^ -o $@


$(NAME): $(OBJS)
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFALGS) $(SRC) -Llibft -lft \
	 -Lft_printf -lftprintf -o $(NAME)

$(SUBDIRS):
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done

clean:
	rm -f $(OBJS)
	for dir in $(SUBDIRS); do \
        $(MAKE) clean -C $$dir; \
    done

fclean: clean
	rm -f $(NAME)
	for dir in $(SUBDIRS); do \
        $(MAKE) fclean -C $$dir; \
    done

re : fclean all

.PHONY: clean fclean all re