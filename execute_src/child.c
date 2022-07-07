/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:38:06 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/07 21:41:41 by ayassin          ###   ########.fr       */
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
	while (temp && (!ft_strchr("<>|", *(temp->token)) || *(temp->token) == 0)) // check flags (and free)
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

int	buitin_switch(t_new *lst, char **env, char *file_name, int append	)
{
	char	**args;

	args = args_array(lst);
	if (args == NULL)
		return (-1); // cahnge number
	ft_tolower_str(lst->token);
	if (lst->token && (ft_strncmp_p(lst->token, "cd", 3) == 0))
		return (ft_chdir(args, env));
	else if (lst->token && (ft_strncmp_p(lst->token, "export", 7) == 0))
		return (ft_export(args, env, file_name, append));
	else if (lst->token && (ft_strncmp_p(lst->token, "unset", 6) == 0))
		return (ft_unset(args, env));
	return (-1);
}

int	child_buitin_switch(char *cmd, char **args, char **env)
{
	int	value;

	value = 0;
	if (cmd && ft_strncmp_p(cmd, "echo", 5) == 0)
		value = ft_echo(args);
	else if (cmd && ft_strncmp_p(cmd, "pwd", 4) == 0)
		value = ft_pwd(args);
	else if (cmd && ft_strncmp_p(cmd, "env", 4) == 0)
		value = ft_env(env, args);
	else if (cmd && (ft_strncmp_p(cmd, "cd", 3) == 0))
		value = ft_chdir(args, env);
	else if (cmd && (ft_strncmp_p(cmd, "export", 7) == 0))
		value = ft_export(args, env, NULL, 0);
	else if (cmd && (ft_strncmp_p(cmd, "unset", 6) == 0))
		value = ft_unset(args, env);
	else
		value = -1;
	if (value != -1)
	{
		close (1);
		close (3);
		free (cmd);
	}
	return (value);
}

int	child_execute(t_new *lst, char **path, char **env)
{
	int		i;
	char	**args;
	int		temp_return;
	char	*clone_cmd;

	i = 0;
	clone_cmd = ft_strdup(lst->token);
	if (!clone_cmd)
		return (-1); // check error
	ft_tolower_str(clone_cmd);
	args = args_array(lst);
	if (args == NULL)
		return (-1);
	temp_return = child_buitin_switch(clone_cmd, args, env);
	if (temp_return != -1)
		return (temp_return);
	if (clone_cmd && (*clone_cmd == '/' || *clone_cmd == '.'))
		execve(clone_cmd, args, env);
	while (path && path[i])
	{
		if (ft_strjoin_ms(&(path[i]), "/") < 0
			|| ft_strjoin_ms(&(path[i]), clone_cmd) < 0)
			break ;
		args[0] = path[i];
		execve(path[i], args, env);
		++i;
	}
	// if (path)
	// 	print_error(ft_strrchr(args[0], '/') + 1, ": command not found");
	// else
		print_error(lst->token, ": command not found", 127);
	free(clone_cmd);
	free(args);
	return (127);
}
