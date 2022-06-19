/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expand2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:39:58 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/19 14:09:14 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_meta(char *str)
{
	int		i;
	char	*s;
	t_list	*tmp;

	i = 0;
	while (str[i] && is_no_dollar_meta(str[i]))
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	tmp = ft_lstnew((void *)(s));
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

char	*get_meta1(char *str)
{
	int		i;
	char	*s;
	t_list	*tmp;

	i = 0;
	while (str[i] && is_no_dollar_meta1(str[i]))
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	tmp = ft_lstnew((void *)(s));
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

int	ft_expand1(t_list **lst, t_list *temp)
{
	t_list	*tmp;

	if (!*lst)
	{
		*lst = ft_lstnew((void *)ft_strdup("$?"));
		tmp = ft_lstnew((void *)(*lst));
		ft_lstadd_back(&g_m, tmp);
	}
	else
	{
		temp = ft_lstnew((void *)ft_strdup("$?"));
		ft_lstadd_back(lst, temp);
		tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
	}
	return (2);
}

int	ft_expand2(t_list **lst, t_list *temp)
{
	t_list	*tmp;

	if (!*lst)
	{
		*lst = ft_lstnew((void *)ft_strdup("$"));
		tmp = ft_lstnew((void *)(*lst));
		ft_lstadd_back(&g_m, tmp);
	}
	else
	{
		temp = ft_lstnew((void *)ft_strdup("$"));
		ft_lstadd_back(lst, temp);
		tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
	}
	return (0);
}

int	ft_expand3(t_list **lst, t_list *temp, char *str, char **env)
{
	t_list	*tmp;

	if (!*lst)
	{
		*lst = ft_lstnew((void *)get_dollar_path(str, env));
		tmp = ft_lstnew((void *)(*lst));
		ft_lstadd_back(&g_m, tmp);
	}
	else
	{
		temp = ft_lstnew((void *)get_dollar_path(str, env));
		ft_lstadd_back(lst, temp);
		tmp = ft_lstnew((void *)(temp));
		ft_lstadd_back(&g_m, tmp);
	}
	return (0);
}
