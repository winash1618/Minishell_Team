/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_assign_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:32:04 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/20 16:25:32 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Functions below is used for variable assignment.
int check_var(char *line, t_info *info)
{
	int c = 0;
	while(*line && ft_isspace(*line))
		line++;
	if (*line == '=')
	{
		info->e_flag = 1;
		return (0);
	}
	else
	{
		if (!is_quote(*line))
			return (0);
		while (*line)
		{
			if (*line == '=')
				c++;
			line++;
		}
		if (c)
			return (1);
	}
	return (0);
}

int get_vars(char *line)
{
	int len = 0;
	while (*line != '=')
	{
		len++;
		line++;
	}
	return (len);
}

int get_len(char *line)
{
	int len = 0;
	while (*line)
	{
		len++;
		line++;
	}
	return (len);
}

char *get_key(char *line)
{
	int len;

	char *temp;
	len = 0;
	len = get_vars(line);
	if(len)
	{
		temp = malloc(sizeof(char) * (len + 1));
		t_list *tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
	}
	int i = 0;
	while (line[i] != '=' && line[i])
	{
		temp[i] = line[i];
		i++;
	}
	temp[i]='\0';
	return (temp);
}

char *get_value(char *line)
{
	int len;
	char *temp;
	len = 0;
	len = get_len(line);
	if(len)
	{
		temp = malloc(sizeof(char) * (len + 1));
		t_list *tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
	}
	int i = 0;
	while (line[i])
	{
		temp[i] = line[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}