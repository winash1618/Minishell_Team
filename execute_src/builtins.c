/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:45:02 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/26 20:25:40 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_chdir(char **args, char **env)
{
	char	*new_loc;

	// do cd (no args);
	if (chdir(args[1]) == -1)
	{		
		if (access(args[1], F_OK))
			print_error(args[1], ": No such file or directory");
		else if (access(args[1], X_OK))
			print_error(args[1], "testdir/: Permission denied");
		else
			print_error(args[1], "green: Not a directory");
		free (args);
		return (1); // correct error code
	}
	new_loc = ft_strdup("PWD=");
	ft_strjoin_ms(&new_loc, getcwd(NULL, 0)); // errors check
	args[1] = new_loc;
	ft_export(args, env);
	return (0);
}