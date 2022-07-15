/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:06:46 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/15 20:07:28 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstadd_backhelper(void *content)
{
	t_list	*node;

	node = ft_lstnew(content);
	if (node == 0)
	{
		free(content);
		return (1);
	}
	ft_lstadd_back(&g_m, node);
	return (0);
}