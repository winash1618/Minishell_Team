/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:38:06 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/22 10:09:31 by ayassin          ###   ########.fr       */
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

int	ft_echo(char **args)
{
	char	flag;
	int		i;

	flag = 1;
	i = 1;
	//ft_putstr_fd("\n", 1);
	while (args[i])
	{
		if (ft_strncmp_p(args[i], "-n", 3) == 0)
			flag = 0;
		else
			ft_printf("%s ", args[i]);
		++i;
	}
	if (flag)
		ft_putstr_fd("\n", 1);
	free(args);
	return (0);
}

int	ft_pwd(char **args)
{
	ft_printf("%s\n", getcwd(NULL, 0));
	free(args);
	return (0);
}

int	ft_env(char **env, char **args)
{
	int		i;

	i = 0;
	while (env[i])
		ft_printf("%s\n", env[i++]);
	free(args);
	return (0);
}

int	child_execute(t_new *lst, char **path, char **env)
{
	int		i;
	char	**args;

	i = 0;
	args = args_array(lst);
	if (args == NULL)
		return (-1);
	if (lst->token && ft_strncmp_p(lst->token, "echo", 5) == 0)
		return (ft_echo(args));
	if (lst->token && (ft_strncmp_p(lst->token, "pwd", 4)
			* ft_strncmp_p(lst->token, "PWD", 4)) == 0)
		return (ft_pwd(args));
	if (lst->token && (ft_strncmp_p(lst->token, "env", 4)
			* ft_strncmp_p(lst->token, "ENV", 4)) == 0)
		return (ft_env(env, args));
	if (lst->token && (*(lst->token) == '/' || *(lst->token) == '.'))
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
	free(args);
	return (-1);
}
