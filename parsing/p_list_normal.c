/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_list_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:22:36 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/22 09:37:33 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// this is for getting words
void	lst_add_new(t_new **pars, char *str, t_info *info)
{
	(*pars)->token = str;
	(*pars)->next = NULL;
	(*pars)->prev = NULL;
	(*pars)->lst = NULL;
	(*pars)->es = NULL;
	if (info)
	{
		if (info->w_flag == 1)
			(*pars)->flag = 1;
		else if (info->w_flag == 3)
			(*pars)->flag = 3;
		else if (info->w_flag == 2)
			(*pars)->flag = 2;
	}
}

void	get_info(t_info *info, t_new *temp)
{
	if (info->w_flag == 1)
		temp->flag = 1;
	else if (info->w_flag == 3)
		temp->flag = 3;
	else if (info->w_flag == 2)
		temp->flag = 2;
}

void	lst_add_back(t_new **pars, char *str, t_info *info, int flag)
{
	t_new	*par;
	t_new	*temp;
	t_list	*tmp;

	par = *pars;
	while ((*pars)->next)
		(*pars) = (*pars)->next;
	temp = malloc(sizeof(t_new));
	tmp = ft_lstnew((void *)(temp));
	ft_lstadd_back(&g_m, tmp);
	temp->token = str;
	temp->es = NULL;
	temp->lst = NULL;
	temp->s_flag = flag;
	if (info)
		get_info(info, temp);
	(*pars)->next = temp;
	temp->next = NULL;
	temp->prev = (*pars);
	(*pars) = par;
}

// for printing purposes
void	lst_print(t_new *pars)
{
	while (pars != NULL)
	{
		printf("<token: %s> <flag: %d> <d_flag: %d> <s_flag: %d> <l_flag: %d> <l2_flag: %d> <r_flag: %d> <r2_flag: %d> <dq_flag: %d>",
			pars->token, pars->flag, pars->d_flag, pars->s_flag, pars->l_flag, 
			pars->l2_flag, pars->r_flag, pars->r2_flag, pars->dq_flag);
		printf("\n");
		pars = pars->next;
	}
}

void	lst_rev_print(t_new *pars)
{
	while (pars && pars->next != NULL)
		pars = pars->next;
	while (pars != NULL)
	{
		printf("<token: %s> <flag: %d> <d_flag: %d> ",
			pars->token, pars->flag, pars->d_flag);
		printf("\n");
		pars = pars->prev;
	}
}
// control - v then enter, gives ^M 