/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:38:06 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/05 16:30:59 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (path[i])
	{
		ft_strjoin_minishell(&(path[i]), "/");
		ft_strjoin_minishell(&(path[i]), lst->token);
		execve(path[i], args, env);
		++i;
	}
	free(args);
	free (env); // temp sol;
	return (1);
}