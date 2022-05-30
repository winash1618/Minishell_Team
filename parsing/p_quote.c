/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:58:25 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/05/30 06:34:00 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// For handling the quotes
#include "../minishell.h"

void quote_counter(char *line, t_info *info)
{
	int c;

	c = 0;
	char *temp; 
	temp = line;
	int d;

	d = 0;
	char *temp2 = ft_strdup(temp);

	int i = 0;
	while (temp2[i])
	{
		if (temp2[i] == '"')
		{
			i++;
			while (temp2[i] != '"' && temp2[i]) 
			{
				temp2[i] = 'a';
				i++;
			}
			if (temp2[i])
				i++;
		}
		else if (temp2[i] == 39)
		{
			i++;
			while (temp2[i] != 39 && temp2[i]) 
			{
				temp2[i] = 'a';
				i++;
			}
			if (temp2[i])
				i++;
		}
		else
			i++;
	}
	i = 0;
	while (temp2[i])
	{
		if (temp2[i] == '"')
			c++;
		else if (temp2[i] == 39)
			d++;
		i++;
	}
	if (c % 2 || d % 2)
		info->q_flag = 1;
}

int ft_strlen_ch(char *line, char c)
{
	int len = 0;
	while(*line != c && *line)
	{
		len++;
		line++;
	}
	return (len);
}

// get the quoted word
char *quoted_word(char *line, char ch)
{
	int i;

	i = 0;
	int len = ft_strlen_ch(line, ch);
	if (len > 0)
	{
		char *s = malloc(sizeof(char) * (len + 1));
		t_list *tmp = ft_lstnew((void *)(s));
		ft_lstadd_back(&g_m, tmp);
		while(line[i] && line[i]!=ch)
		{
			s[i] = line[i];
			i++;
		}
		s[i] = '\0';
		return (s);
	}
	return (NULL);
}

// move the pointer after the quote
char *go_past_quotes(char *s, char ch)
{
	// printf("%s \n", s);
	while (*s != ch && *s)
		s++;
	if(*s == ch)
		s++;
	return (s);
}