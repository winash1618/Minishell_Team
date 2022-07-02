/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:45:02 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/02 20:01:13 by ayassin          ###   ########.fr       */
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
	close(1); // temp place
	close(3);
	return (0);
}

int	ft_pwd(char **args)
{
	char	*my_dir;

	my_dir = getcwd(NULL, 0);
	ft_printf("%s\n", my_dir);
	if (my_dir)
		free(my_dir);
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

void	go_to_headdir(void)
{
	char	*new_loc;
	char	*temp_loc;

	new_loc = NULL;
	temp_loc = NULL;
	while (ft_strlen(new_loc) != ft_strlen(temp_loc) || temp_loc == NULL)
	{
		if (new_loc)
			free(new_loc);
		new_loc = getcwd(NULL, 0);
		chdir("..");
		if (temp_loc)
			free(temp_loc);
		temp_loc = getcwd(NULL, 0);
	}
	if (temp_loc)
		free(temp_loc);
	if (new_loc)
		free(new_loc);
}

// void	go_to_headdir2(void)
// {
// 	char	*temp_loc;

// 	temp_loc = getcwd(NULL, 0);
// 	while (temp_loc[1] != '\0')
// 	{
// 		chdir("..");
// 		if (temp_loc)
// 			free(temp_loc);
// 		temp_loc = getcwd(NULL, 0);
// 	}
// 	if (temp_loc)
// 		free(temp_loc);
// }

int	ft_chdir(char **args, char **env)
{
	char	*home;
	char	*old_loc;

	old_loc = getcwd(NULL, 0);
	if (args[1] == NULL || args[1][0] == '~') // make it fail
	{
		home = get_home(env);
		if (home && *home != '\0')
		{
			go_to_headdir();
			chdir(home);
			if (args[1] && args[1][1] != '\0' && chdir(&args[1][2]) == -1)
			{
				go_to_headdir();
				chdir(old_loc);
				print_error(&args[1][1], ": No such file or directory");
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
		if (old_loc)
			free(old_loc);
		free (args);
		return (1); // correct error code
	}
	// new_loc = ft_strdup("PWD="); // protect
	// ft_strjoin_ms(&new_loc, getcwd(NULL, 0)); // errors check
//	ft_export(&new_loc, env);
	if (old_loc)
		free(old_loc);
	free(args);
	return (0);
}
