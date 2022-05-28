/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:16:46 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/28 06:20:49 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <sys/wait.h>
# include <unistd.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "parsing/parser.h"

int	excute(t_new *lst, char **env);


#endif