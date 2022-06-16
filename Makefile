# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 08:40:39 by ayassin           #+#    #+#              #
#    Updated: 2022/06/16 14:54:59 by ayassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

PNAME = parser

SRC = minishell.c $(EXECUTE_SRC_INDIR)
 
EXECUTE_SRC = pipex.c pipex_utils.c child.c redirection.c redirection2.c \
				temp_list.c here_doc.c

EXECUTE_SRC_DIR = execute_src
				
EXECUTE_SRC_INDIR = $(addprefix $(EXECUTE_SRC_DIR)/,$(EXECUTE_SRC))

EXECUTE_OBJ_DIR =  execute_objs

SRCP = parser.c

SUBDIRS = libft ft_printf parsing

OBJS = $(SRC:.c=.o)

OBJSP = $(SRCP:.c=.o)

CC = gcc

CFLAGS = -g3 -Wall -Werror -Wextra 

all: $(NAME)

%.o : %.c
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFLAGS) -Ilibft -Ift_printf -Iparsing -c $^ -o $@


$(NAME): $(OBJS) $(OBJSP)
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFALGS) $(SRC)  -lreadline \
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