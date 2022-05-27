/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 07:33:02 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/05/27 09:57:45 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_meta(char c)
{
	if (ft_strchr("	 \n|&;()<>$", c))
	{
		return (1);
	}
	return (0);
}

int get_strlen(char *str)
{
	int i = 0;
	while (str[i] && !is_meta(str[i]))
	{
		i++;
	} 
	return (i);
}

int	ft_strjoin_ps(char **prestr, char *sufstr, int8_t freesuf)
{
	int		i1;
	int		i2;
	char	*fullstr;

	i1 = 0;
	i2 = 0;
	fullstr = (char *)malloc(ft_strlen(*prestr) + ft_strlen(sufstr) + 1);
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
	// if (*prestr)
	// 	free (*prestr);
	if (freesuf)
		free (sufstr);
	*prestr = fullstr;
	return (1);
}

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


int main(int ac, char **argv, char **env)
{
	ac++;
	(void)argv;
	char *s = get_expanded_string("a($PATH&$PATH&|a$PATHfsd", env);
	// char *s = get_dollar_path("fsd", env);
	// int s = get_strlen("aPATH&$PATH&|a");
	ft_printf("hi %s\n", s);
	// printf("hi");
}