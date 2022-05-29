/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:49:39 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/05/28 17:28:10 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void find_redirection_presence(t_new *cmd)
{
	while(cmd != NULL)
	{
		cmd->d_flag = 0;
		int i = 0;
		while(cmd->token[i])
		{
			if (cmd->token[i] == '>')
			{
				if (cmd->token[i + 1] == '>' )
					cmd->r2_flag = 1;
				else
					cmd->r_flag = 1;
			}
			else if (cmd->token[i] == '<')
			{
				if (cmd->token[i + 1] == '<')
					cmd->l2_flag = 1;
				else
					cmd->l_flag = 1;
			}
			i++;
		}
		cmd = cmd->next;
	}
}