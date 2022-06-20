/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 10:36:18 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/20 11:41:25 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lst_join(t_new *cmd)
{
	if ((cmd)->next != NULL)
	{
		cmd = (cmd)->next;
		while (cmd != NULL)
		{
			if (cmd->next)
			{
				cmd = (cmd)->next;
				if ((cmd)->s_flag == -1)
				{
					(cmd)->prev->token = ft_strjoin((cmd)->prev->token,
							(cmd)->token);
					lst_skip_node2(cmd);
					if (!cmd->next)
					{
						(cmd)->prev->next = NULL;
						break ;
					}
				}
			}
			else
			{
				if ((cmd)->s_flag == -1)
				{
					(cmd)->prev->token = ft_strjoin((cmd)->prev->token,
							(cmd)->token);
					cmd->prev->next = NULL;
				}
				break ;
			}
		}
	}
}
