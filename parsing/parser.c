#include "../minishell.h"

int is_meta(char c)
{
	if (ft_strchr("	 \n|&;()<>$", c))
	{
		return (1);
	}
	return (0);
}

char	*ft_strnstr1(const char *haystack, const char *needle, size_t len)
{
	size_t	pos;
	size_t	i;

	pos = 0;
	i = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[pos] && pos < len)
	{
		while (haystack[pos + i] == needle[i] && (pos + i) < len)
		{
			i++;
			if (!needle[i])
				return ((char *)&(haystack[pos]));
		}
		i = 0;
		pos++;
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
	printf("%d\n", len);
	printf("%s\n", s);
	// (void)env;
	s1 = NULL;
	while(env[i] && len)
	{
		printf("%s \n", env[i]);
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
	printf("%s", s1);
	if (!s1)
		s1= "";
	// if (!s1)
	// 	return (NULL);
	// return ("Hi");
	return (s1);
}

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


int main(int ac, char **argv, char **env)
{
	ac++;
	(void)argv;
	// char *s = get_expanded_string("a($PATH&$PATH&|a", env);
	char *s = get_dollar_path("SECURITYSESSION", env);
	// int s = get_strlen("aPATH&$PATH&|a");
	ft_printf("hi %s\n", s);
	// printf("hi");
}