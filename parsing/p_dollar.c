/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_dollar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:36:54 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/05/28 17:28:44 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void find_dollar_presence(t_new *cmd)
{
	while(cmd != NULL)
	{
		cmd->d_flag = 0;
		int i = 0;
		while(cmd->token[i])
		{
			if (cmd->token[i] == '$')
				cmd->d_flag = 1;
			i++;
		}
		
		cmd = cmd->next;
	}
}

void dollar_expansion(t_new *cmd, char **env)
{
	while (cmd != NULL)
	{
		if (cmd->d_flag)
		{
			if (cmd->flag == 1 || cmd->flag == 2)
				cmd->es = get_expanded_string(cmd->token, env);
			else
				cmd->lst = get_expanded_list(cmd->token, env);
		}
		cmd = cmd->next;
	}
}