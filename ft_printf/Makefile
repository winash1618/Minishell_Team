# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/13 09:20:21 by ayassin           #+#    #+#              #
#    Updated: 2022/05/28 06:52:02 by mkaruvan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printfhelper.c ft_printf.c

BNS_SRC = ft_printfhelper1_bonus.c ft_printfhelper2_bonus.c\
		 ft_printfhelper3_bonus.c ft_printf_bonus.c

DIRS = ../libft

CC = gcc

CFLAGS = -g3 -Werror -Wall -Wextra


OBJS = $(SRC:.c=.o)

BNS_OBJS = $(BNS_SRC:.c=.o)


all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I../libft -c $^ -o $@

$(NAME): $(SUBDIRS) $(OBJS)
	ar cr  $(NAME) $(OBJS)

bonus: $(BNS_OBJS)
	ar cr $(NAME) $(BNS_OBJS)

clean:
	rm -f $(OBJS) $(BNS_OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean libft

