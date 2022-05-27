# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 08:40:39 by ayassin           #+#    #+#              #
#    Updated: 2022/05/27 16:33:39 by mkaruvan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

Headers = minishell.h

SRC = minishell.c pipex.c

PARSE = parser.c p_assign_1.c p_assign_2.c p_dollar.c \
		p_expand.c p_list_assign.c p_list_normal.c \
		p_normal.c p_quote.c p_utils_1.c p_utils_2.c \
		prompt.c

SUBDIRS = libft ft_printf

PDIR = parsing

PNAME = parser

OBJS = $(SRC:.c=.o)

POBJS = $(addprefix $(PDIR)/, $(PARSE:%c=%o))

PSRC = $(addprefix $(PDIR)/, $(PARSE))

CC = gcc

CFLAGS = -g3 -Wall -Werror -Wextra 

all: $(NAME)

$(PDIR)/%.o : $(PDIR)/%.c
			@mkdir -p $(PDIR)
			@$(CC) $(CFLAGS) -Ilibft -Ift_printf  -c $< -o $@
.c.o:
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFLAGS) -Ilibft -Ift_printf -c $^ -o $@


$(NAME): $(OBJS) $(POBJS)
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done
	$(CC) $(CFALGS) $(SRC) -Llibft -lft \
	 -Lft_printf -lftprintf -o $(NAME)
	$(CC) $(CFALGS) $(PSRC) -Llibft -lft \
	 -Lft_printf -lftprintf -ltermcap -lreadline -o $(PNAME)

$(SUBDIRS):
	for dir in $(SUBDIRS); do \
        $(MAKE) all -C $$dir; \
    done

clean:
	rm -f $(OBJS)
	rm -f $(PDIR)/*.o
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