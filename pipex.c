/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:30:18 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/25 17:35:42 by ayassin          ###   ########.fr       */
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

int	excute(t_new *lst, char **env)
{
	//int	pipes_num;
	char	**paths;
	int		i;

	i = 0;
	(void)lst;
	//Find Path
	while (*env && !ft_strnstr(*env, "PATH=", 5))
		env++;
	*env = ft_strnstr(*env, "PATH=", 5);

	//Check if path is ther
	if (*env == NULL)
		return (0);
	
	//split path
	paths = ft_split(*env + 5, ':');
	
	while (paths[i])
	{
		//execve(path[i],)
		ft_printf("%s\n", paths[i]);
		++i;
	}
	clear_str_sep(paths);
	return (0);
}