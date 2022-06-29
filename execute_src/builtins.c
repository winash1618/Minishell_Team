/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:45:02 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/29 18:20:33 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **args)
{
	char	flag;
	int		i;

	flag = 1;
	i = 1;
	while (args[i])
	{
		if (ft_strncmp_p(args[i], "-n", 3) == 0)
			flag = 0;
		else
		{
			ft_printf("%s", args[i]);
			if (args[i + 1])
				ft_printf(" ");
		}	
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
	{
		if (ft_strchr(env[i], '=') != 0)
			ft_printf("%s\n", env[i]);
		++i;
	}
	free(args);
	return (0);
}

char	*get_home(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "HOME=", 5) == 0)
			return (&env[i][5]);
		++i;
	}
	return (NULL);
}

int	ft_chdir(char **args, char **env)
{
	char	*new_loc;
	char	*home;
	char	*old_loc;

	new_loc = NULL;
	old_loc = getcwd(NULL, 0);
	if (args[1] == NULL || args[1][0] == '~') // make it fail
	{
		home = get_home(env);
		if (home && *home != '\0')
		{
			while (ft_strlen(new_loc) != ft_strlen(getcwd(NULL, 0)))
			{
				new_loc = getcwd(NULL, 0);
				chdir("..");
			}
			chdir(home);
			if (args[1] && args[1][1] != '\0' && chdir(&args[1][2]) == -1)
			{
				while (ft_strlen(new_loc) != ft_strlen(getcwd(NULL, 0)))
				{
					new_loc = getcwd(NULL, 0);
					chdir("..");
				}
				chdir(old_loc);
				print_error(&args[1][2], ": No such file or directory");
			}
		}
	}
	else if (chdir(args[1]) == -1)
	{	
		if (access(args[1], F_OK))
			print_error(args[1], ": No such file or directory");
		else if (access(args[1], X_OK))
			print_error(args[1], ": Permission denied");
		else
			print_error(args[1], ": Not a directory");
		free (args);
		return (1); // correct error code
	}
	// new_loc = ft_strdup("PWD="); // protect
	// ft_strjoin_ms(&new_loc, getcwd(NULL, 0)); // errors check
//	ft_export(&new_loc, env);
	free(args);
	return (0);
}
