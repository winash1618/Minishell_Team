/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:38:06 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/29 16:46:09 by ayassin          ###   ########.fr       */
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

int	buitin_switch(t_new *lst, char **args, char **env)
{
	if (lst->token && (ft_strncmp_p(lst->token, "cd", 3) == 0))
		return (ft_chdir(args, env));
	else if (lst->token && (ft_strncmp_p(lst->token, "export", 7) == 0))
		return (ft_export(args, env));
	else if (lst->token && (ft_strncmp_p(lst->token, "unset", 6) == 0))
		return (ft_unset(args, env));
	return (-1);
}

int	child_buitin_switch(t_new *lst, char **args, char **env)
{
	if (lst->token && ft_strncmp_p(lst->token, "echo", 5) == 0)
		return (ft_echo(args));
	else if (lst->token && (ft_strncmp_p(lst->token, "pwd", 4)
			* ft_strncmp_p(lst->token, "PWD", 4)) == 0)
		return (ft_pwd(args));
	else if (lst->token && (ft_strncmp_p(lst->token, "env", 4)
			* ft_strncmp_p(lst->token, "ENV", 4)) == 0)
		return (ft_env(env, args));
	else if (lst->token && (ft_strncmp_p(lst->token, "cd", 3) == 0))
		return (ft_chdir(args, env));
	else if (lst->token && (ft_strncmp_p(lst->token, "export", 7) == 0))
		return (ft_export(args, env));
	else if (lst->token && (ft_strncmp_p(lst->token, "unset", 6) == 0))
		return (ft_unset(args, env));
	return (-1);
}

int	child_execute(t_new *lst, char **path, char **env)
{
	int		i;
	char	**args;
	int		temp_return;

	i = 0;
	args = args_array(lst);
	if (args == NULL)
		return (-1);
	temp_return = child_buitin_switch(lst, args, env);
	if (temp_return != -1)
		return (temp_return);
	if (lst->token && (*(lst->token) == '/' || *(lst->token) == '.'))
		execve(lst->token, args, env);
	while (path && path[i])
	{
		if (ft_strjoin_ms(&(path[i]), "/") < 0
			|| ft_strjoin_ms(&(path[i]), lst->token) < 0)
			break ;
		args[0] = path[i];
		execve(path[i], args, env);
		++i;
	}
	if (path)
		print_error(ft_strrchr(args[0], '/') + 1, ": command not found");
	else
		print_error(lst->token, ": command not found");
	errno = 127;
	free(args);
	return (-1);
}
