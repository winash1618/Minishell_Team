/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 10:36:18 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/07/03 16:42:00 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_metardp(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int checks(t_new *cmd)
{
	if (is_metardp(cmd->token[0]) && (cmd->flag == 4))
	{
		if (cmd->next)
			cmd->next->s_flag = 0;
		return (0);
	}
	else if (cmd->s_flag != -1)
		return (0);
	
	// if (cmd->s_flag == -1 && !is_metardp(cmd->prev->token[0]) && (cmd->flag == 1 || cmd->flag == 2))
	// if ((cmd)->s_flag == -1 && (!ft_strchr("<>|",
	// 		(cmd)->prev->token[0]) || ((cmd)->prev->token[0] == 0)))
	// 		{
	// 			return (1);
	// 		}
	// else if((cmd)->s_flag == -1 && (ft_strchr("<>|",
	// 		(cmd)->prev->token[0]) || ((cmd)->prev->token[0] == 0)) && 
	// 		(cmd->flag == 1 || cmd->flag == 2))
	// 		return (1);
	// else if ((cmd)->s_flag == -1 && (cmd->flag == 4) && (!ft_strchr("<>|",
	// 		(cmd)->prev->token[0]) || ((cmd)->prev->token[0] == 0)))
	// 		return (1);
			
	return (1);
}

int	ft_lst_join_help(t_new *cmd)
{
	if (checks(cmd))
	{
		(cmd)->prev->token = ft_strjoin((cmd)->prev->token,
				(cmd)->token);
		ft_lstadd_back(&g_m, ft_lstnew((void *)((cmd)->prev->token)));
		lst_skip_node2(cmd);
		if (!cmd->next)
		{
			(cmd)->prev->next = NULL;
			return (1);
		}
	}
	return (0);
}

void	ft_lst_join(t_new *cmd)
{
	if ((cmd)->next != NULL)
	{
		cmd = (cmd)->next;
		while (cmd != NULL)
		{
			if (cmd->next)
			{
				if (ft_lst_join_help(cmd))
					break ;
				cmd = (cmd)->next;
			}
			else
			{
				if (checks(cmd))
				{
					(cmd)->prev->token = ft_strjoin((cmd)->prev->token,
							(cmd)->token);
					ft_lstadd_back(&g_m, ft_lstnew((void *)((cmd)->prev->token)));
					cmd->prev->next = NULL;
				}
				break ;
			}
		}
	}
}
