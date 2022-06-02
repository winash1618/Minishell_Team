/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:54:24 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/02 09:04:36 by ayassin          ###   ########.fr       */
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

void	temp_list_clear(t_new **lst)
{
	t_new	*temp;
	t_new	*tempnext;

	if (lst)
	{
		temp = *lst;
		while (temp != 0)
		{
			tempnext = temp -> next;
			free(temp);
			temp = tempnext;
		}
		*lst = 0;
	}
}

int	list_has_pipes(t_new *lst)
{
	if (lst == NULL)
		return (0);
	while (lst)
	{
		if (*(lst->token) == '|')
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	print_strarr(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		ft_printf("\"%s\" ", args[i++]);
	ft_printf("\n");
}

int	number_of_pipes(t_new *lst)
{
	int	count;

	count = 0;
	if (lst == NULL)
		return (0);
	while (lst)
	{
		if (*(lst->token) == '|')
			++count;
		lst = lst->next;
	}
	return (count);
}