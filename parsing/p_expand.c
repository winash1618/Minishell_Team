/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:27:21 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/05 13:19:03 by mkaruvan         ###   ########.fr       */
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
	while (str[i] && !is_meta(str[i]))
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	t_list *tmp = ft_lstnew((void *)(s));
	ft_lstadd_back(&g_m, tmp);
	i = 0;
	while (str[i] && !is_meta(str[i]))
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char *get_meta(char *str)
{
	int i;
	char *s;

	i = 0;
	while (str[i] && is_no_dollar_meta(str[i]))
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	t_list *tmp = ft_lstnew((void *)(s));
	ft_lstadd_back(&g_m, tmp);
	i = 0;
	while (str[i] && is_no_dollar_meta(str[i]))
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char *get_meta1(char *str)
{
	int i;
	char *s;
	
	i = 0;
	while (str[i] && is_no_dollar_meta1(str[i]))
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	t_list *tmp = ft_lstnew((void *)(s));
	ft_lstadd_back(&g_m, tmp);
	i = 0;
	while (str[i] && is_no_dollar_meta1(str[i]))
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

void ft_expand1(t_list **lst, t_list *temp)
{
	if (!*lst)
	{
		*lst = ft_lstnew((void *)ft_strdup("$?"));
		t_list *tmp = ft_lstnew((void *)(*lst));
		ft_lstadd_back(&g_m, tmp);
	}
	else
	{
		temp = ft_lstnew((void *)ft_strdup("$?"));// errno is 
		ft_lstadd_back(lst, temp);
		t_list *tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
	}
}

void ft_expand2(t_list **lst, t_list *temp)
{
	if (!*lst)
	{
		*lst = ft_lstnew((void *)ft_strdup("$"));
		t_list *tmp = ft_lstnew((void *)(*lst));
		ft_lstadd_back(&g_m, tmp);
	}
	else
	{
		temp = ft_lstnew((void *)ft_strdup("$"));// errno is 
		ft_lstadd_back(lst, temp);
		t_list *tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
	}
}

void ft_expand3(t_list **lst, t_list *temp, char *str, char **env)
{
	if (!*lst)
	{
		*lst = ft_lstnew((void *)get_dollar_path(str, env));
		t_list *tmp = ft_lstnew((void *)(*lst));
		ft_lstadd_back(&g_m, tmp);
	}
	else
	{
		temp = ft_lstnew((void *)get_dollar_path(str, env));
		ft_lstadd_back(lst, temp);
		t_list *tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
	}
}

void ft_expand4(t_list **lst, t_list *temp, char *str)
{
	if (!*lst)
	{
		*lst = ft_lstnew((void *)get_meta(str));
		t_list *tmp = ft_lstnew((void *)(*lst));
		ft_lstadd_back(&g_m, tmp);
	}
	else
	{
		temp = ft_lstnew((void *)get_meta(str));
		ft_lstadd_back(lst, temp);
		t_list *tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
	}
}

void ft_expand5(t_list **lst, t_list *temp, char *str)
{
	if (!*lst)
	{
		*lst = ft_lstnew((void *)get_meta1(str));
		t_list *tmp = ft_lstnew((void *)(*lst));
		ft_lstadd_back(&g_m, tmp);
	}
	else
	{
		temp = ft_lstnew((void *)get_meta1(str));
		ft_lstadd_back(lst, temp);
		t_list *tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
	}
}

void ft_expand6(t_list **lst, t_list *temp, char *str)
{
	if (!*lst)
	{
		*lst = ft_lstnew((void *)get_str(str));
		t_list *tmp = ft_lstnew((void *)(*lst));
		ft_lstadd_back(&g_m, tmp);
	}
	else
	{
		temp = ft_lstnew((void *)get_str(str));
		ft_lstadd_back(lst, temp);
		t_list *tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
	}
}

t_list *get_expanded_list(char *str, char **env)
{
	int i = 0;
	errno = 0;
	t_list *lst;
	lst = NULL;
	t_list *temp;
	while(str[i])
	{
		temp = NULL;
		if (str[i] == '$' && str[i + 1] == '?')
		{
			ft_expand1(&lst, temp);
			// if (!lst)
			// {
			// 	lst = ft_lstnew((void *)ft_strdup("$?"));
			// 	t_list *tmp = ft_lstnew((void *)(lst));
			// 	ft_lstadd_back(&g_m, tmp);
			// }
			// else
			// {
			// 	temp = ft_lstnew((void *)ft_strdup("$?"));// errno is 
			// 	ft_lstadd_back(&lst, temp);
			// 	t_list *tmp = ft_lstnew((void *)(temp));
			// 	ft_lstadd_back(&g_m, tmp);
			// }
			i = i + 2;
		}
		else if(str[i] == '$' && !str[i + 1])
		{
			ft_expand2(&lst, temp);
			// if (!lst)
			// {
			// 	lst = ft_lstnew((void *)ft_strdup("$"));
			// 	t_list *tmp = ft_lstnew((void *)(lst));
			// 	ft_lstadd_back(&g_m, tmp);
			// }
			// else
			// {
			// 	temp = ft_lstnew((void *)ft_strdup("$"));// errno is 
			// 	ft_lstadd_back(&lst, temp);
			// 	t_list *tmp = ft_lstnew((void *)(temp));
			// 	ft_lstadd_back(&g_m, tmp);
			// }
			break;
		}
		else if (str[i] == '$')
		{
			ft_expand3(&lst, temp, str + i + 1, env);
			// if (!lst)
			// {
			// 	lst = ft_lstnew((void *)get_dollar_path(str + i + 1, env));
			// 	t_list *tmp = ft_lstnew((void *)(lst));
			// 	ft_lstadd_back(&g_m, tmp);
			// }
			// else
			// {
			// 	temp = ft_lstnew((void *)get_dollar_path(str + i + 1, env));
			// 	ft_lstadd_back(&lst, temp);
			// 	t_list *tmp = ft_lstnew((void *)(temp));
			// 	ft_lstadd_back(&g_m, tmp);
			// }
			i = i + get_strlen(str + i + 1) + 1;
		}
		else if (is_no_dollar_meta(str[i]))
		{
			ft_expand4(&lst, temp, str + i);
			// if (!lst)
			// {
			// 	lst = ft_lstnew((void *)get_meta(str + i));
			// 	t_list *tmp = ft_lstnew((void *)(lst));
			// 	ft_lstadd_back(&g_m, tmp);
			// }
			// else
			// {
			// 	temp = ft_lstnew((void *)get_meta(str + i));
			// 	ft_lstadd_back(&lst, temp);
			// 	t_list *tmp = ft_lstnew((void *)(temp));
			// 	ft_lstadd_back(&g_m, tmp);
			// }
			while (str[i] && is_no_dollar_meta(str[i]))
				i++;
		}
		else if (is_no_dollar_meta1(str[i]))
		{
			ft_expand5(&lst, temp, str + i);
			// if (!lst)
			// {
			// 	lst = ft_lstnew((void *)get_meta1(str + i));
			// 	t_list *tmp = ft_lstnew((void *)(lst));
			// 	ft_lstadd_back(&g_m, tmp);
			// }
			// else
			// {
			// 	temp = ft_lstnew((void *)get_meta1(str + i));
			// 	ft_lstadd_back(&lst, temp);
			// 	t_list *tmp = ft_lstnew((void *)(temp));
			// 	ft_lstadd_back(&g_m, tmp);
			// }
			while (str[i] && is_no_dollar_meta1(str[i]))
				i++;
		}
		else 
		{
			ft_expand6(&lst, temp, str + i);
			// if (!lst)
			// {
			// 	lst = ft_lstnew((void *)get_str(str + i));
			// 	t_list *tmp = ft_lstnew((void *)(lst));
			// 	ft_lstadd_back(&g_m, tmp);
			// }
			// else
			// {
			// 	temp = ft_lstnew((void *)get_str(str + i));
			// 	ft_lstadd_back(&lst, temp);
			// 	t_list *tmp = ft_lstnew((void *)(temp));
			// 	ft_lstadd_back(&g_m, tmp);
			// }
			while (str[i] && !is_meta(str[i]))
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
		printf("%s \n",(char *)lst->content);
		ft_strjoin_ps(&s, (char *)lst->content, 0);
		lst = lst->next;
	}
	// printf("%s \n", s);
	return (s);
}