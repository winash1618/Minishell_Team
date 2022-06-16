/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:38:06 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/16 18:07:04 by ayassin          ###   ########.fr       */
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
	if (lst->token && *(lst->token) == '/')
		execve(lst->token, args, env);
	while (path[i])
	{
		if (ft_strjoin_minishell(&(path[i]), "/") < 0
			|| ft_strjoin_minishell(&(path[i]), lst->token) < 0)
			break ;
		args[0] = path[i];
		execve(path[i], args, env);
		++i;
	}
	print_error(ft_strrchr(args[0], '/') + 1, ": command not found");
	free(args);
	return (-1);
}
