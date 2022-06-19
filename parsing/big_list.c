/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 09:49:19 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/19 16:13:58 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lst_add_front(t_new **cmd, t_list *lst)
{
	t_new	*temp;
	t_list	*tmp;

	while (lst)
	{
		temp = malloc(sizeof(t_new));
		tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
		temp->token = (char *)lst->content;
		temp->es = NULL;
		temp->lst = NULL;
		temp->d_flag = 0;
		temp->flag = 4;
		temp->l_flag = 0;
		temp->l2_flag = 0;
		temp->r_flag = 0;
		temp->r2_flag = 0;
		(*cmd)->prev->next = temp;
		temp->prev = (*cmd)->prev;
		temp->next = (*cmd);
		(*cmd)->prev = temp;
		lst = lst->next;
	}
}

void	lst_big_new(t_new **cmd, t_list *lst)
{
	t_new	*temp;
	t_list	*tmp;

	while (lst)
	{
		temp = malloc(sizeof(t_new));
		tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
		temp->token = (char *)lst->content;
		temp->es = NULL;
		temp->lst = NULL;
		temp->d_flag = 0;
		temp->flag = 4;
		if ((*cmd)->prev == NULL)
			temp->prev = NULL;
		else
		{
			temp->prev = (*cmd)->prev;
			(*cmd)->prev->next = temp;
		}
		temp->next = (*cmd);
		(*cmd)->prev = temp;
		lst = lst->next;
	}
}

void	lst_add(t_new **cmd, t_list *lst)
{
	if ((*cmd)->prev == NULL)
		lst_big_new(cmd, lst);
	else
		lst_add_front(cmd, lst);
}

void	lst_skip_node2(t_new *cmd)
{
	if (cmd->prev)
		cmd->prev->next = cmd->next;
	if (cmd->next)
		cmd->next->prev = cmd->prev;
}

void	make_big_list(t_new **cmd)
{
	t_new	*temp;

	temp = (*cmd);
	while ((*cmd) != NULL)
	{
		if ((*cmd)->lst != NULL)
			big_list_help(cmd);
		(*cmd) = (*cmd)->next;
	}
	*cmd = temp;
	while ((*cmd)->prev)
		*cmd = (*cmd)->prev;
}
