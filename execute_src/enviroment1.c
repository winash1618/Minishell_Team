/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:31:30 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/17 18:33:30 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putenv_fd(char **env, int fd)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", fd);
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			write(fd, &(env[i][j++]), 1);
		if (env[i][j] == '=')
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(&(env[i][j + 1]), fd);
			ft_putstr_fd("\"", fd);
		}
		write(fd, "\n", 1);
		++i;
	}
}

int	display_env(char **env, char *file_name, int append)
{
	int	fd;

	append = (O_APPEND * (append)) | (O_TRUNC * (!append));
	if (file_name == NULL)
		fd = 1;
	else
		fd = open(file_name, O_WRONLY | append);
	if (fd < 0)
		return (1);
	ft_putenv_fd(env, fd);
	if (file_name && fd > 0)
		close(fd);
	return (0);
}

int	append_env(char **env, char **args, int i, int j)
{
	char	**new_env;

	if (env[j] && ft_strchr(args[i], '=') != 0)
	{
		env[j] = ft_strdup(args[i]);
		if (!env[j])
			return (1);
		return (ft_lstadd_backhelper(&g_m, env[j]));
	}
	else if (!env[j])
	{
		new_env = (char **)malloc(sizeof(*env) * (j + 2));
		if (!new_env)
			return (1);
		if (ft_lstadd_backhelper(&g_m, new_env))
		{
			free(new_env);
			return (1);
		}
		if (cpynewenv(new_env, env))
			return (1);
		env[j] = args[i];
		env[j + 1] = NULL;
	}
	return (0);
}

int	export_loop(char **env, char **args)
{
	int		prelen;
	int		i;
	int		j;
	int		error;

	i = 1;
	error = 0;
	while (args[i] != NULL)
	{
		if (!valid_varible(args[i]))
		{
			error += print_error(args[i++], ": not a valid identifier", 1);
			continue ;
		}
		if (ft_strchr(args[i], '=') != 0)
			prelen = ft_strchr(args[i], '=') - args[i];
		else
			prelen = ft_strlen(args[i]);
		j = 0;
		while (env [j] && ft_strncmp_p(env[j], args[i], prelen) != 0)
			++j;
		error += append_env(env, args, i, j);
		++i;
	}
	return (error);
}

int	ft_export(char **args, char **env, char *file_name, int append)
{
	int		error;

	error = 0;
	if (args[1] == NULL)
		error = display_env (env, file_name, append);
	else
		error = export_loop(env, args);
	free(args);
	if (error)
		return (1);
	return (0);
}
