/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:49:39 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/01 13:37:54 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void make_others_zero(t_new *cmd)
{
	if (cmd->r2_flag != 1)
		cmd->r2_flag = 0;
	if (cmd->r_flag != 1)
		cmd->r_flag = 0;
	if (cmd->l2_flag != 1)
		cmd->l2_flag = 0;
	if (cmd->l_flag != 1)
		cmd->l_flag = 0;
	if (cmd->p_flag != 1)
		cmd->p_flag = 0;
}

void make_all_zero(t_new *cmd)
{
	while(cmd != NULL)
	{
		cmd->r2_flag = 0;
		cmd->r_flag = 0;
		cmd->l2_flag = 0;
		cmd->l_flag = 0;
		cmd->p_flag = 0;
		// printf("%d %d %d %d \n", cmd->r2_flag, cmd->r_flag, cmd->l2_flag, cmd->l_flag);
		cmd = cmd->next;
	}
}

void find_redirection_presence(t_new *cmd)
{
	while(cmd != NULL)
	{
		int i = 0;
		if (cmd->flag == 3)
		{
			while(cmd->token[i])
			{
				if (cmd->token[i] == '>')
				{
					if (cmd->token[++i] == '>' )
						cmd->r2_flag = 1;
					else
						cmd->r_flag = 1;
					break;
				}
				else if (cmd->token[i] == '<')
				{
					if (cmd->token[++i] == '<')
						cmd->l2_flag = 1;
					else
						cmd->l_flag = 1;
					break;
				}
				i++;
			}
			i = 0;
			while(cmd->token[i])
			{
				if (cmd ->token[i] == '|')
				{
					cmd->p_flag = 1;
				}
				i++;
			}
		}
		else
		{
			break;
		}
		make_others_zero(cmd);
		printf("%d %d %d %d %d\n", cmd->r2_flag, cmd->r_flag, cmd->l2_flag, cmd->l_flag, cmd->p_flag);
		cmd = cmd->next;
	}
}