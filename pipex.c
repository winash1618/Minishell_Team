/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:30:18 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/29 12:15:43 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* free the output of ft_split after we are done with it*/
void	clear_str_sep(char **str_sep)
{
	int	i;

	i = 0;
	if (str_sep)
	{
		while (str_sep[i])
			free(str_sep[i++]);
		free (str_sep);
	}
}

/*Appends suffex string "sufstr" to the prefix string "prestr" 
up until "sufstr" char 0 or new line. 
Return 1 if sufstr has new lone, -1 if Memory allocation failed, 0 otherwise
**malloc DANGER**/
int	ft_strjoin_minishell(char **prestr, char *sufstr)
{
	int		i1;
	int		i2;
	int		lineflag;
	char	*fullstr;

	i1 = 0;
	i2 = 0;
	lineflag = 0;
	fullstr = (char *)malloc(ft_strlen(*prestr) + ft_strlen(sufstr) + 1);
	if (fullstr == NULL)
		return (-10);
	while (*prestr && (*prestr)[i1])
	{
		fullstr[i1] = (*prestr)[i1];
		++i1;
	}
	while (sufstr[i2] && sufstr[i2] != '\n')
		fullstr[i1++] = sufstr[i2++];
	fullstr[i1] = 0;
	if (*prestr)
		free (*prestr);
	*prestr = fullstr;
	return (lineflag);
}

int	child1(t_new *lst, char **path, char **env)
{
	int		i;
	char	*limits;
	int		arg_count;
	t_new	*temp;
	char	**args;

	limits = "<>|";
	arg_count = 0;
	temp = lst;
	while (temp && !ft_strchr(limits, *(temp->token))) // check flags (and free)
	{
		++arg_count;
		temp = temp->next;
	}
	args = (char **)malloc(sizeof(*args) * (arg_count + 1));
	i = 0;
	temp = lst;
	while (i < arg_count)
	{
		args[i++] = temp->token;
		temp = temp->next;
	}
	args[i] = NULL;
	i = 0;
	while (path[i])
	{
		ft_strjoin_minishell(&(path[i]), "/");
		ft_strjoin_minishell(&(path[i]), lst->token);
		// char * args[] = {path[i], "Makefile", NULL};
		//ft_printf("%s\n", path[i]);
		execve(path[i], args, env);
		++i;
	}
	return (1);
}

int	excute(t_new *lst, char **env)
{
	char	**path;
	int		i;
	int		id;
	int		status;

	i = 0;
	status = 0;
	(void)lst;
	//Find Path
	while (env[i] && !ft_strnstr(env[i], "PATH=", 5))
		++i;
	env[i] = ft_strnstr(env[i], "PATH=", 5);
	//Check if path is ther
	if (env[i] == NULL)
		return (0);
	// split path
	//ft_printf("%s\n", env[i]);
	path = ft_split(env[i] + 5, ':');
	i = 0;
	id = 0;
	while (id == 0 && lst)
	{
		id = fork();
		if (id != 0)
			child1 (lst, path, env);
		else
		{
			while (lst && *(lst->token) != '|') //use flag
				lst = lst->next;
			if (lst && *(lst->token) == '|') //use flag
				lst = lst->next;
			waitpid(id, &status, 0);
		}
	}
	// clear ing the split
	if (id != 0)
	{
		ft_printf("The parent is alive\n");
	}
	clear_str_sep(path);
	return (0);
}