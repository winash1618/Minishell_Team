/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redirection2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:55:44 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/07/02 18:14:20 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//------------------------------------------------------------------
//----------------------------Error Handling------------------------
//------------------------------------------------------------------

int	is_rpd(char c)
{
	if (ft_strchr("<>|/", c)) // pssible strchr prolblem
		return (1);
	return (0);
}

int	find_lderror(char *str, t_new *cmd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
		{
			if (str[i + 2] == '|' || (!str[i + 2] && !cmd->next))
				return (ft_putstr_fd1("Wrong syntax \n", 2));
			else if (str[i + 2] == '<' || str[i + 2] == '>')
				return (ft_putstr_fd1("Wrong syntax \n", 2));
		}
		else if (str[i] == '>' && str[i + 1] == '<')
			return (ft_putstr_fd1("Wrong syntax \n", 2));
		else if (str[i] == '>' && str[i + 1] == '|')
			return (ft_putstr_fd1("Wrong syntax \n", 2));
		i++;
	}
	return (0);
}

int	find_rderror(char *str, t_new *cmd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			if (str[i + 2] == '|' || (!str[i + 2] && !cmd->next))
				return (ft_putstr_fd1("Wrong syntax \n", 2));
			else if (str[i + 2] == '<' || str[i + 2] == '>')
				return (ft_putstr_fd1("Wrong syntax \n", 2));
		}
		else if (str[i] == '<' && str[i + 1] == '>')
			return (ft_putstr_fd1("Wrong syntax \n", 2));
		else if (str[i] == '<' && str[i + 1] == '|')
			return (ft_putstr_fd1("Wrong syntax \n", 2));
		if (str[i] == '>' || str[i] == '<')
			if (!str[i + 1] && !cmd->next)
				return (ft_putstr_fd1("Wrong syntax \n", 2));
		i++;
	}
	return (0);
}

int	find_perror(char *str, t_new *cmd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == '|' || (!str[i + 1] && !cmd->next))
				return (ft_putstr_fd1("Wrong syntax \n", 2));
			else if (str[i + 1] == '\0' && cmd->next)
			{
				if (cmd->next->token[0] == '|')
					return (ft_putstr_fd1("Wrong syntax \n", 2));
			}
			else if (str[i + 1] == '<' || str[i + 1] == '>')
			{
				if (is_meta_pipe(str[i + 2]))
					if (!str[i + 2])
						return (ft_putstr_fd1("Wrong syntax \n", 2));
			}
		}
		i++;
	}
	return (0);
}

int	syntax_error(t_new *cmd)
{
	int	flag;

	flag = 0;
	while (cmd != NULL)
	{
		if (cmd->flag == 3)
		{
			flag += find_rderror(cmd->token, cmd);
			if (!flag)
				flag += find_lderror(cmd->token, cmd);
			if (!flag)
				flag += find_perror(cmd->token, cmd);
		}
		cmd = cmd->next;
	}
	return (flag);
}
