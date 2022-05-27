/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:58:25 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/05/27 15:15:38 by mkaruvan         ###   ########.fr       */
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
	while (*line)
	{
		if (*line == '"')
			c++;
		line++;
	}
	if (c % 2)
		info->q_flag = 1;
	c = 0;
	while (*temp)
	{
		if (*temp == '"')
			c++;
		temp++;
	}
	if (c % 2)
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