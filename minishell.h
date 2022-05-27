/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:16:46 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/27 06:36:41 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

// for saving local variable
typedef struct var 
{
	char		*key;
	char		*value;
	struct var	*next;
	struct var	*prev;
}	t_var;

// for saving commands
typedef struct list
{
	char		*token;
	int			flag;
	char		**var;
	char		**temp;
	int			dollar_flag;
	struct list	*next;
	struct list	*prev;
}	t_new;

typedef struct info
{
	int	flag;
	int	w_flag;
}				t_info;

int	excute(t_new *lst, char **env);
#endif