#include "../minishell.h"

// int is_meta(char c)
// {
// 	if (ft_strchr("	 \n|&;()<>$", c))
// 	{
// 		return (1);
// 	}
// 	return (0);
// }

// int get_strlen(char *str)
// {
// 	int i = 0;
// 	while (str[i] && !is_meta(str[i]))
// 	{
// 		i++;
// 	} 
// 	return (i);
// }

// char *get_dollar_path(char *str, char **env)
// {
// 	int i = 0;
// 	int len = get_strlen(str);
// 	char *s = ft_substr(str, 0, len);
// 	char *s1;
// 	s1 = NULL;
// 	while(env[i])
// 	{
// 		s1 = ft_strnstr(env[i], s, len);
// 		s1 = s1 + len;
// 		i++;
// 	}
// 	if (!s1)
// 		return (NULL);
// 	return (s1);
// }

// char *get_expanded_string(char *str, char **env)
// {
// 	int i = 0;
// 	char *s;

// 	s = NULL;
// 	while(str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			s = get_dollar_path(str + i + 1, env);
// 			i = i + get_strlen(str + i + 1) + 1;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while(str[i])
// 	{
// 		if (str[i] == '$')
// 		{
			
// 			i = i + get_strlen(str + i + 1) + 1;
// 		}
// 		i++;
// 	}
// 	if (!s)
// 		return (NULL);
// 	return (s);
// }
#include <stdio.h>
int main(int ac, char **argv, char **env)
{
	ac++;
	(void)argv;
	(void)env;
// 	char *s = get_expanded_string("a($PATH&$PATH&|a", env);
// 	ft_printf("%s \n", s);
	printf("hi");
}