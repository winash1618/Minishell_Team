#include "minishell.h"

t_list *g_m;

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

int is_meta_pipe(char c)
{
	if (ft_strchr("|", c))
	{
		return (1);
	}
	return (0);
}

char *get_meta_pipe(char *str)
{
	int i;
	char *s;

	i = 0;
	while (str[i] && is_meta_pipe(str[i]))
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	t_list *tmp = ft_lstnew((void *)(s));
	ft_lstadd_back(&g_m, tmp);
	i = 0;
	while (str[i] && is_meta_pipe(str[i]))
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



t_list *get_expanded_list(char *str, char **env)
{
	int i = 0;
	errno = 0;
	t_list *lst;
	lst = NULL;
	t_list *temp;
	while(str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			if (!lst)
			{
				lst = ft_lstnew((void *)ft_strdup("$?"));
				t_list *tmp = ft_lstnew((void *)(lst));
				ft_lstadd_back(&g_m, tmp);
			}
			else
			{
				temp = ft_lstnew((void *)ft_strdup("$?"));// errno is 
				ft_lstadd_back(&lst, temp);
				t_list *tmp = ft_lstnew((void *)(temp));
				ft_lstadd_back(&g_m, tmp);
			}
			i = i + 2;
		}
		else if(str[i] == '$' && !str[i + 1])
		{
			
			if (!lst)
			{
				lst = ft_lstnew((void *)ft_strdup("$"));
				t_list *tmp = ft_lstnew((void *)(lst));
				ft_lstadd_back(&g_m, tmp);
			}
			else
			{
				temp = ft_lstnew((void *)ft_strdup("$"));// errno is 
				ft_lstadd_back(&lst, temp);
				t_list *tmp = ft_lstnew((void *)(temp));
				ft_lstadd_back(&g_m, tmp);
			}
			break;
		}
		else if (str[i] == '$')
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
		else if (is_no_dollar_meta(str[i]))
		{
			
			if (!lst)
			{
				lst = ft_lstnew((void *)get_meta(str + i));
				t_list *tmp = ft_lstnew((void *)(lst));
				ft_lstadd_back(&g_m, tmp);
			}
			else
			{
				temp = ft_lstnew((void *)get_meta(str + i));
				ft_lstadd_back(&lst, temp);
				t_list *tmp = ft_lstnew((void *)(temp));
				ft_lstadd_back(&g_m, tmp);
			}
			while (str[i] && is_no_dollar_meta(str[i]))
				i++;
		}
		else if (is_meta_pipe(str[i]))
		{
			if (!lst)
			{
				lst = ft_lstnew((void *)get_meta_pipe(str + i));
				t_list *tmp = ft_lstnew((void *)(lst));
				ft_lstadd_back(&g_m, tmp);
			}
			else
			{
				temp = ft_lstnew((void *)get_meta_pipe(str + i));
				ft_lstadd_back(&lst, temp);
				t_list *tmp = ft_lstnew((void *)(temp));
				ft_lstadd_back(&g_m, tmp);
			}
			while (str[i] && is_meta_pipe(str[i]))
				i++;
		}
		else if (is_no_dollar_meta1(str[i]))
		{
			
			if (!lst)
			{
				lst = ft_lstnew((void *)get_meta1(str + i));
				t_list *tmp = ft_lstnew((void *)(lst));
				ft_lstadd_back(&g_m, tmp);
			}
			else
			{
				temp = ft_lstnew((void *)get_meta1(str + i));
				ft_lstadd_back(&lst, temp);
				t_list *tmp = ft_lstnew((void *)(temp));
				ft_lstadd_back(&g_m, tmp);
			}
			while (str[i] && is_no_dollar_meta1(str[i]))
				i++;
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

int main(int ac, char **argv, char **env)
{
	ac++;
	(void)argv;
	char *s = get_expanded_string(">>fsd", env);
	// char *s = get_expanded_string(">|", env);
	// char *s = get_dollar_path("fsd", env);
	// int s = get_strlen("aPATH&$PATH&|a");
	// char *s = get_meta(">>>fsd");
	// ft_printf("hi %s\n", s);
	// printf("hi");
}
