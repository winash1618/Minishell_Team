# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 08:40:39 by ayassin           #+#    #+#              #
#    Updated: 2022/05/29 08:47:04 by mkaruvan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

PNAME = parser

SRC = minishell.c pipex.c temp_list.c

SRCP = parser.c

SUBDIRS = libft ft_printf parsing

OBJS = $(SRC:.c=.o)

OBJSP = $(SRCP:.c=.o)

CC = gcc

CFLAGS = -ggdb -Wall -Werror -Wextra 

all: $(NAME)

.c.o:
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFLAGS) -Ilibft -Ift_printf -Iparsing -c $^ -o $@


$(NAME): $(OBJS) $(OBJSP)
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFALGS) $(SRC)  \
	-Lft_printf -lftprintf parsing/parsing.a -Llibft -lft -o $(NAME)
	$(CC) $(CFALGS) $(SRCP)  \
	 parsing/parsing.a \
	 -Lft_printf -lftprintf -Llibft -lft -ltermcap -lreadline -o $(PNAME)


clean:
	rm -f $(OBJS)
	rm -f $(OBJSP)
	for dir in $(SUBDIRS); do \
        $(MAKE) clean -C $$dir; \
    done

fclean: clean
	rm -f $(NAME)
	rm -f $(PNAME)
	for dir in $(SUBDIRS); do \
        $(MAKE) fclean -C $$dir; \
    done

re : fclean all

.PHONY: clean fclean all re