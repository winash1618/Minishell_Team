/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:53:57 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/26 18:22:02 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Normal utilities
#include "../minishell.h"

// to check for spaces
int	ft_isspace(char c)
{
	if (c == '\n' || c == ' ' || c == '	')
		return (1);
	return (0);
}

// to check for quotes
int	is_quote(char c)
{
	if (c == '"' || c == 39)
		return (0);
	return (1);
}

void	normal_lexer(t_new **pars, t_info *info, char *str)
{
	int		wc;
	char	*temp;
	int		flag;

	wc = 0;
	flag = 1;
	while (*str)
	{
		info->w_flag = 0;
		while (*str && ft_isspace(*str))
			str++;
		wc = normal_lexer_help(pars, info, str, wc);
		if (*str == '"')
			temp = go_past_quotes(++str, '"', &flag);
		else if (*str == 39)
			temp = go_past_quotes(++str, 39, &flag);
		while (*str && !ft_isspace(*str) && flag && is_quote(*str))
			str++;
		if (!flag)
		{
			str = temp;
			flag = 1;
		}
	}
}

int	ft_strjoin_ps(char **prestr, char *sufstr, int8_t freesuf)
{
	int		i1;
	int		i2;
	char	*fullstr;
	t_list	*tmp;

	i1 = 0;
	i2 = 0;
	fullstr = (char *)malloc(ft_strlen(*prestr) + ft_strlen(sufstr) + 1);
	tmp = ft_lstnew((void *)(fullstr));
	ft_lstadd_back(&g_m, tmp);
	if (fullstr == NULL)
		return (0);
	while (*prestr && (*prestr)[i1])
	{
		fullstr[i1] = (*prestr)[i1];
		++i1;
	}
	while (sufstr && sufstr[i2])
		fullstr[i1++] = sufstr[i2++];
	fullstr[i1] = 0;
	if (freesuf)
		free (sufstr);
	*prestr = fullstr;
	return (1);
}

// char	*ft_combine_from_list(t_new *cmd)
// {
// 	char	*s;
// 	t_list	*lst;

// 	s = "";
// 	lst = cmd->lst;
// 	while (lst)
// 	{
// 		if (ft_strncmp((char *)lst->content, "$?", 2))
// 			ft_strjoin_ps(&s, ft_itoa(errno), 0);
// 		else
// 			ft_strjoin_ps(&s, (char *)lst->content, 0);
// 		lst = lst->next;
// 	}
// 	return (s);
// }

void	big_list_help(t_new **cmd)
{
	char	*str;
	t_list	*tmp;

	tmp = (*cmd)->lst;
	if ((*cmd)->flag == 3)
	{
		lst_add(cmd, tmp);
		lst_skip_node2(*cmd);
	}
	if ((*cmd)->flag == 1)
	{
		// if ((*cmd)->dq_flag == 1)
		// 	str = ft_combine_from_list(*cmd);
		// else
		str = ft_strdup((*cmd)->es);
		tmp = ft_lstnew((void *)(str));
		ft_lstadd_back(&g_m, tmp);
		(*cmd)->token = str;
	}
}
