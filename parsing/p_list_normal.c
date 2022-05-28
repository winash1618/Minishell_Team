/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_list_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:22:36 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/05/28 10:39:10 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// this is for getting words
void lst_add_new(t_new **pars, char *str, t_info *info)
{
	(*pars)->token = str;
	(*pars)->next = NULL;
	(*pars)->prev = NULL;
	if (info)
	{
		if (info->w_flag == 1)
			(*pars)->flag = 1;
		else if (info->w_flag == 3)
			(*pars)->flag = 3;
	}
	
}
void lst_add_back(t_new **pars, char *str, t_info *info)
{
	t_new *par;
	par = *pars;
	t_new *temp;
	while ((*pars)->next)
	{
		(*pars) = (*pars)->next;
	}
	temp = malloc(sizeof(t_new));
	temp->token = str;
	if (info)
	{
		if (info->w_flag == 1)
		temp->flag = 1;
		else if (info->w_flag == 3)
			(temp)->flag = 3;
	}
	(*pars)->next = temp;
	temp->next = NULL;
	temp->prev = (*pars);
	(*pars) = par;
}

// for printing purposes

void lst_print(t_new *pars)
{
	while(pars != NULL)
	{
		printf("<token: %s> <flag: %d> <d_flag: %d", pars->token, pars->flag, pars->d_flag);
		pars= pars->next;
	}
}