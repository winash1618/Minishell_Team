/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:38:06 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/22 09:45:23 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**args_array(t_new *lst)
{
	int		arg_count;
	t_new	*temp;
	char	**args;
	int		i;

	arg_count = 0;
	temp = lst;
	while (temp && !ft_strchr("<>|", *(temp->token))) // check flags (and free)
	{
		++arg_count;
		temp = temp->next;
	}
	args = (char **)malloc(sizeof(*args) * (arg_count + 1));
	if (args == NULL)
		return (NULL);
	i = 0;
	temp = lst;
	while (i < arg_count)
	{
		args[i++] = temp->token;
		temp = temp->next;
	}
	args[i] = NULL;
	return (args);
}

int	child_execute(t_new *lst, char **path, char **env)
{
	int		i;
	char	**args;

	i = 0;
	args = args_array(lst);
	if (args == NULL)
		return (-1);
	if (lst->token && ft_strncmp_p(lst->token, "./", 3))
		execve(lst->token, args, env);
	if (lst->token && *(lst->token) == '/')
		execve(lst->token, args, env);
	while (path[i])
	{
		if (ft_strjoin_ms(&(path[i]), "/") < 0
			|| ft_strjoin_ms(&(path[i]), lst->token) < 0)
			break ;
		args[0] = path[i];
		execve(path[i], args, env);
		++i;
	}
	print_error(ft_strrchr(args[0], '/') + 1, ": command not found");
	errno = 127;
	free(args);
	return (-1);
}
