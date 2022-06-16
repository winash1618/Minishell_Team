/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:49:39 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/14 17:47:17 by mkaruvan         ###   ########.fr       */
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


void redirection_help(t_new *cmd)
{
	int i;
	
	i = 0;
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
}

void pipe_help(t_new *cmd)
{
	int i;
	
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

void find_redirection_presence(t_new *cmd)
{
	make_all_zero(cmd);
	while(cmd != NULL)
	{
		if (cmd->flag == 3)
		{
			redirection_help(cmd);
			pipe_help(cmd);
		}
		make_others_zero(cmd);
		// printf("%d %d %d %d %d\n", cmd->r2_flag, cmd->r_flag, cmd->l2_flag, cmd->l_flag, cmd->p_flag);
		cmd = cmd->next;
	}
}

//------------------------------------------------------------------
//----------------------------Error Handling------------------------
//------------------------------------------------------------------

int find_lderror(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
		{
			if (str[i + 2] == '|')
			{
				ft_putstr_fd("Wrong syntax", 2);
				return (1);
			}
			else if (str[i + 2] == '<' || str[i + 2] == '>')
			{
				ft_putstr_fd("Wrong syntax", 2);
				return (1);
			}
		}
		else if (str[i] == '>' && str[i + 1] == '<')
		{
			ft_putstr_fd("Wrong syntax", 2);
			return (1);
		}
		else if (str[i] == '>' && str[i + 1] == '|')
		{
			ft_putstr_fd("Wrong syntax", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int find_rderror(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			if (str[i + 2] == '|')
			{
				ft_putstr_fd("Wrong syntax", 2);
				return (1);
			}
			else if (str[i + 2] == '<' || str[i + 2] == '>')
			{
				ft_putstr_fd("Wrong syntax", 2);
				return (1);
			}
		}
		else if (str[i] == '<' && str[i + 1] == '>')
		{
			ft_putstr_fd("Wrong syntax", 2);
			return (1);
		}
		else if (str[i] == '<' && str[i + 1] == '|')
			exit(0);
		i++;
	}
	return (0);
}

int find_perror(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '|' )
		{
			if (str[i + 1] == '|')
			{
				ft_putstr_fd("Wrong syntax", 2);
				return (1);
			}
			else if (str[i + 1] == '<' || str[i + 1] == '>')
			{
				ft_putstr_fd("Wrong syntax", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int syntax_error(t_new *cmd)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while(cmd != NULL)
	{
		if (cmd->flag == 3)
		{
			flag = find_rderror(cmd->token);
			flag = find_lderror(cmd->token);
			flag = find_perror(cmd->token);
		}
		cmd = cmd->next;
	}
	return (flag);
}

