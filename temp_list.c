/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:54:24 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/29 08:51:18 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
t_new	*temp_lst_newnode(char *str)
{
	t_new	*lst;

	lst = (t_new *)malloc(sizeof(*lst));
	lst->es = NULL;
	lst->lst = NULL;
	lst->next = NULL;
	lst->prev = NULL;
	lst->token = str;
	lst->d_flag = 0;
	return (lst);
}

void	temp_lstadd_back(t_new **lst, t_new *node)
{
	t_new	*back;

	if (!lst || !node)
		return ;
	if (*lst == NULL)
	{
		*lst = node;
		node->next = NULL;
		node->prev = NULL;
		return ;
	}
	back = *lst;
	while (back->next)
	{
		back = back->next;
	}
	node->next = NULL;
	node->prev = back;
	back->next = node;
}