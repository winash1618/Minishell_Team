# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 08:40:39 by ayassin           #+#    #+#              #
#    Updated: 2022/06/20 16:25:47 by ayassin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

PNAME = parser

SRC = minishell.c $(EXECUTE_SRC_INDIR) $(EXECUTE_SRC_INDIR1)
 
EXECUTE_SRC = pipex.c pipex_utils.c  pipex_utils1.c child.c redirection.c \
				redirection2.c temp_list.c here_doc.c signals.c
				
EXECUTE_SRC1 = p_assign_1.c p_assign_2.c p_dollar.c \
		p_expand.c p_list_assign.c p_list_normal.c \
		p_normal.c p_quote.c p_utils_1.c p_utils_2.c \
		prompt.c p_redirection.c big_list.c p_redirection2.c \
		p_expand1.c p_expand2.c p_expand3.c p_expand4.c  join_list.c\

EXECUTE_SRC_DIR = execute_src
				
EXECUTE_SRC_INDIR = $(addprefix $(EXECUTE_SRC_DIR)/,$(EXECUTE_SRC))

EXECUTE_SRC_DIR1 = parsing
				
EXECUTE_SRC_INDIR1 = $(addprefix $(EXECUTE_SRC_DIR1)/,$(EXECUTE_SRC1))

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
	$(CC) $(CFALGS) $(SRC) -ltermcap -lreadline \
	-Lft_printf -lftprintf -Llibft -lft -o $(NAME)
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