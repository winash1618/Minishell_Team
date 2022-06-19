/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redirection2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:55:44 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/19 14:57:38 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//------------------------------------------------------------------
//----------------------------Error Handling------------------------
//------------------------------------------------------------------

int	ft_putstr_fd1(char *s, int fd)
{
	if (s)
		while (*s)
			write(fd, s++, 1);
	return (1);
}

int	find_lderror(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
		{
			if (str[i + 2] == '|' || !str[i + 2])
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

int	find_rderror(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			if (str[i + 2] == '|' || !str[i + 2])
				return (ft_putstr_fd1("Wrong syntax \n", 2));
			else if (str[i + 2] == '<' || str[i + 2] == '>')
				return (ft_putstr_fd1("Wrong syntax \n", 2));
		}
		else if (str[i] == '<' && str[i + 1] == '>')
			return (ft_putstr_fd1("Wrong syntax \n", 2));
		else if (str[i] == '<' && str[i + 1] == '|')
			return (ft_putstr_fd1("Wrong syntax \n", 2));
		i++;
	}
	return (0);
}

int	find_perror(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' )
		{
			if (str[i + 1] == '|' || !str[i + 1])
				return (ft_putstr_fd1("Wrong syntax \n", 2));
			else if (str[i + 1] == '<' || str[i + 1] == '>')
				return (ft_putstr_fd1("Wrong syntax \n", 2));
		}
		i++;
	}
	return (0);
}

int	syntax_error(t_new *cmd)
{
	int	i;
	int	flag;
	int	flag_n;

	i = 0;
	flag = 0;
	flag_n = 0;
	printf ("%d %d\n", flag, cmd->flag);
	while (cmd != NULL)
	{
		if (cmd->flag == 3)
		{
			flag += find_rderror(cmd->token);
			flag += find_lderror(cmd->token);
			flag += find_perror(cmd->token);
		}
		cmd = cmd->next;
	}
	return (flag);
}
