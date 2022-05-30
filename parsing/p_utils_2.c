/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:53:57 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/05/29 17:19:02 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Normal utilities
#include "../minishell.h"

// to check for spaces
int ft_isspace(char c)
{
	if (c == '\n' || c == ' ' || c == '	')
		return (1);
	return (0);
}

// to check for quotes
int is_quote(char c)
{
	if (c == '"' || c == 39)
		return (0);
	return (1);
} 