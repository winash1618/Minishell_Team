/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 09:49:19 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/07/03 18:17:39 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	check(int i, char *str, char *s2, int j)
// {
// 	if (!*s2 && i == -1)
// 		return (i);
// 	if (j == 1 || j == 2)
// 		return (i);
// 	if (!is_no_dollar_meta(*str) && !is_meta_pipe(*str))
// 		if (!is_no_dollar_meta(*s2) && !is_meta_pipe(*s2))
// 			return (i);
// 	return (1);
// }

// int	check1(int i, char *str, int j)
// {
// 	if (j == 1 || j == 2)
// 		return (i);
// 	if (!is_no_dollar_meta(*str) && !is_meta_pipe(*str))
// 		return (i);
// 	return (1);
// }

void	lst_add_front(t_new **cmd, t_list *lst)
{
	t_new	*temp;

	while (lst)
	{
		temp = malloc(sizeof(t_new));
		ft_lstadd_back(&g_m, ft_lstnew((void *)(temp)));
		temp->token = (char *)lst->content;
		temp->es = NULL;
		temp->lst = NULL;
		temp->d_flag = 0;
		temp->flag = 4;
		temp->s_flag = (*cmd)->s_flag;
		// check((*cmd)->s_flag, (temp)->token,
		// 		(*cmd)->prev->token, (*cmd)->flag);
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

	while (lst)
	{
		temp = malloc(sizeof(t_new));
		ft_lstadd_back(&g_m, ft_lstnew((void *)(temp)));
		temp->token = (char *)lst->content;
		temp->es = NULL;
		temp->lst = NULL;
		temp->d_flag = 0;
		temp->flag = 4;
		temp->s_flag = (*cmd)->s_flag;//check1((*cmd)->s_flag, (temp)->token, (*cmd)->flag);
		if ((*cmd)->prev == NULL)
			temp->prev = NULL;
		else
		{
			temp->s_flag = (*cmd)->s_flag; //check((*cmd)->s_flag, (temp)->token,
					//(*cmd)->prev->token, (*cmd)->flag);
			temp->prev = (*cmd)->prev;
			(*cmd)->prev->next = temp;
		}
		temp->next = (*cmd);
		(*cmd)->prev = temp;
		lst = lst->next;
	}
}
