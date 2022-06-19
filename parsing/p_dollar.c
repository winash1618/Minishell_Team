/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_dollar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:36:54 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/18 17:09:51 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void find_dollar_presence(t_new *cmd)
{
	int i;
	
	while(cmd != NULL)
	{
		cmd->d_flag = 0;
		if (cmd->flag != 2)
		{
			i = 0;
			while(cmd->token[i])
			{
				if (cmd->token[i] == '$')
					cmd->d_flag = 1;
				i++;
			}
		}
		cmd = cmd->next;
	}
}

// int check_special_meta(char *str)
// {
// 	while (*str)
// 	{
// 		if (*str == )
// 		str++;
// 	}
// }

// int redirection_exist(t_list *lst)
// {
// 	while(lst)
// 	{
// 		if ((char *)lst->content[0] == '|' || (char *)lst->content[0] == '>' || (char *)lst->content[0] == '<') 
// 			return (1)
// 		lst = lst->next;
// 	}
// 	return (0);
// }
void dollar_expansion(t_new *cmd, char **env)
{
	while (cmd != NULL)
	{
		// if (cmd->d_flag)
		// {
			// if (cmd->flag != 2)
			// {
			// 	cmd->es = get_expanded_string(cmd->token, env);
			// 	cmd->lst = get_expanded_list(cmd->token, env);
				
			// }
			if (cmd->flag == 1)
			{
				cmd->es = get_expanded_string(cmd->token, env);
				cmd->lst = get_expanded_list(cmd->token, env);
				
			}
			if (cmd->flag == 3)
			{
				cmd->lst = get_expanded_list(cmd->token, env);
				// if (redirection_exist(cmd->lst))
				// {
					cmd->lst = get_expanded_string2(cmd->token, env);
				// }
				// cmd->lst = get_expanded_list(cmd->token, env);
				
			}
		// }
		cmd = cmd->next;
	}
}