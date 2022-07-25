/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:06:46 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/25 09:26:35 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstadd_backhelper(t_list **head, void *content)
{
	t_list	*node;

	node = ft_lstnew(content);
	if (node == 0)
	{
		if (content)
			free(content);
		return (print_error("", "malloc failed", 1));
	}
	ft_lstadd_back(head, node);
	return (0);
}

void	cleanexit(char **path, int (*fd)[2], int status, int *open_fds)
{
	int	i;

	i = 3;
	while (i >= 0)
		close(i--);
	if (open_fds)
	{
		close(open_fds[0]);
		close(open_fds[1]);
	}
	if (fd)
		free(fd);
	clear_str_sep(path);
	ft_lstclear(&g_m, free);
	exit(status);
}

int	builtins(t_new *lst, char **env)
{
	char	*armrest1;
	char	*out_file_name;
	int		legrests[2];
	t_new	*temp;

	armrest1 = NULL;
	out_file_name = NULL;
	legrests[0] = 0;
	legrests[1] = 0;
	temp = lst;
	if (list_has_pipes(temp))
		return (1);
	if (redirect_loop(&temp, &armrest1, &out_file_name, legrests))
		return (1);
	find_cmd(&lst);
	return (buitin_switch(lst, env, out_file_name, legrests[0]));
}

void	find_cmd(t_new **lst)
{
	t_new	*node;

	node = *lst;
	if (!node)
		return ;
	while (node)
	{
		if (node->flag == 4 && (*(node->token) == '>' || *(node->token) == '<'))
		{
			node = node->next;
			if (node)
				node = node->next;
			continue ;
		}
		else if (node->flag == 4 && ft_strchr(node->token, '=')
			&& valid_varible(node->token))
		{
			node = node->next;
			continue ;
		}
		break ;
	}
	*lst = node;
}

int	has_parentbuiltins(t_new *lst)
{
	if (list_has_pipes(lst))
		return (0);
	find_cmd(&lst);
	if (!lst)
		return (0);
	else if (lst->token && (ft_strncmp_pc(lst->token, "cd", 3) == 0))
		return (1);
	else if (lst->token && (ft_strncmp_pc(lst->token, "export", 7) == 0))
		return (1);
	else if (lst->token && (ft_strncmp_pc(lst->token, "unset", 6) == 0))
		return (1);
	return (0);
}
