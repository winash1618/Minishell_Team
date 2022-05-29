/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:27:21 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/05/29 07:27:31 by mkaruvan         ###   ########.fr       */
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
	{
		s = ft_substr(str, 0, len);
		t_list *tmp = ft_lstnew((void *)(s));
		ft_lstadd_back(&g_m, tmp);
	}
	s1 = NULL;
	while(env[i] && len)
	{
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
	if (!s1)
		s1= "";
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
	t_list *tmp = ft_lstnew((void *)(s));
		ft_lstadd_back(&g_m, tmp);
	i = 0;
	while (str[i] && str[i] != '$')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

t_list *get_expanded_list(char *str, char **env)
{
	int i = 0;
	
	t_list *lst;
	lst = NULL;
	t_list *temp;
	while(str[i])
	{
		if (str[i] == '$')
		{
			if (!lst)
			{
				lst = ft_lstnew((void *)get_dollar_path(str + i + 1, env));
				t_list *tmp = ft_lstnew((void *)(lst));
				ft_lstadd_back(&g_m, tmp);
			}
			else
			{
				temp = ft_lstnew((void *)get_dollar_path(str + i + 1, env));
				ft_lstadd_back(&lst, temp);
				t_list *tmp = ft_lstnew((void *)(temp));
				ft_lstadd_back(&g_m, tmp);
			}
			i = i + get_strlen(str + i + 1) + 1;
		}
		else
		{
			if (!lst)
			{
				lst = ft_lstnew((void *)get_str(str + i));
				t_list *tmp = ft_lstnew((void *)(lst));
				ft_lstadd_back(&g_m, tmp);
			}
			else
			{
				temp = ft_lstnew((void *)get_str(str + i));
				ft_lstadd_back(&lst, temp);
				t_list *tmp = ft_lstnew((void *)(temp));
				ft_lstadd_back(&g_m, tmp);
			}
			while (str[i] && str[i] != '$')
				i++;
		}
	}
	return (lst);
}

char *get_expanded_string(char *str, char **env)
{
	char *s;
	s = "";
	t_list *lst = get_expanded_list(str, env);

	while (lst)
	{
		ft_strjoin_ps(&s, (char *)lst->content, 0);
		lst = lst->next;
	}
	printf("%s \n", s);
	return (s);
}