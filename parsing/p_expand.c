/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:27:21 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/05/27 14:32:01 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_dollar_path(char *str, char **env)
{
	int i;
	char *s;
	char *s1;
	int len;

	len = 0;
	len = get_strlen(str);
	i = 0;
	s = NULL;
	if (len)
		s = ft_substr(str, 0, len);
	// printf("%d\n", len);
	// printf("%s\n", s);
	// (void)env;
	s1 = NULL;
	while(env[i] && len)
	{
		// printf("%s \n", env[i]);
		s1 = ft_strnstr(env[i], s, len);
		if (s1)
		{
			s1 = s1 + len;
			if (*s1 == '=')
				s1++;
			else
				return ("");
			break;
		}
		i++;
	}
	// printf("%s", s1);
	if (!s1)
		s1= "";
	// if (!s1)
	// 	return (NULL);
	// return ("Hi");
	return (s1);
}

char *get_str(char *str)
{
	int i;
	char *s;
	
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '$')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	// printf("----%s----", s);
	return (s);
}

char *get_expanded_string(char *str, char **env)
{
	int i = 0;
	char *s;
	t_list *lst;
	t_list *tmp;

	s = "";
	while(str[i])
	{
		if (str[i] == '$')
		{
			if (!lst)
				lst = ft_lstnew((void *)get_dollar_path(str + i + 1, env));
			else
			{
				tmp = ft_lstnew((void *)get_dollar_path(str + i + 1, env));
				ft_lstadd_back(&lst, tmp);
			}
			i = i + get_strlen(str + i + 1) + 1;
			// printf ("===%c===", str[i]);
		}
		else
		{
			if (!lst)
				lst = ft_lstnew((void *)get_str(str + i));
			else
			{
				tmp = ft_lstnew((void *)get_str(str + i));
				ft_lstadd_back(&lst, tmp);
			}
			while (str[i] && str[i] != '$')
				i++;
		}
	}
	while (lst)
	{
		ft_strjoin_ps(&s, (char *)lst->content, 0);
		lst = lst->next;
	}
	printf("%s \n", s);
	// i = 0;
	// while(str[i])
	// {
	// 	if (str[i] == '$')
	// 	{
	// 		i = i + get_strlen(str + i + 1) + 1;
	// 	}
	// 	i++;
	// }
	// if (!s)
	// 	return (NULL);
	return ("sf");
}