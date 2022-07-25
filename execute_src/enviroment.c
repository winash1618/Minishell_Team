/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:44:36 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/25 09:28:47 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cpynewenv(char **new_env, char **env)
{
	int		count;

	count = 0;
	if (!env)
		return (0);
	while (env[count])
	{
		new_env[count] = ft_strdup(env[count]);
		if (new_env[count] == NULL)
			return (print_error("", "malloc failed", 1));
		if (ft_lstadd_backhelper(&g_m, new_env[count]))
			return (1);
		++count;
	}
	new_env[count] = NULL;
	*env = *new_env;
	return (0);
}

int	setnewenv(char **env)
{
	int		count;
	char	**new_env;

	count = 0;
	new_env = NULL;
	while (env && env[count])
		++count;
	if (count)
	{
			new_env = (char **)malloc((sizeof(*new_env) + 1) * count);
		if (!new_env)
			return (print_error("", "malloc failed", 1));
		if (ft_lstadd_backhelper(&g_m, new_env))
			return (1);
		return (cpynewenv(new_env, env));
	}
	return (0);
}

int	valid_varible(char *var)
{
	int	i;

	i = 0;
	if (!var || !*var || !(ft_isalpha(*var) || *var == '_'))
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (!(ft_isalnum(var[i]) || var[i] == '_'))
			return (0);
		++i;
	}
	return (1);
}

void	ft_unset_helper(char *args, char **env)
{
	int	i;
	int	prelen;

	i = 0;
	prelen = ft_strlen(args) + 1;
	while (env [i] && !((ft_strncmp_p(env[i], args, prelen) == '=')
			|| (ft_strncmp_p(env[i], args, prelen) == 0
				&& ft_strchr(env[i], '=') == NULL)))
		++i;
	while (env[i] && env [i + 1])
	{
		env[i] = env[i + 1];
		++i;
	}
	env[i] = NULL;
}

int	ft_unset(char **args, char **env)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (args[i] != NULL)
	{
		if (!valid_varible(args[i]) || ft_strchr(args[i], '=') != 0)
		{
			error = print_error(args[i++], ": not a valid identifier", 1);
			continue ;
		}
		ft_unset_helper(args[i], env);
		++i;
	}
	free(args);
	return (error);
}

/*
int	ft_export(char **args, char **env, char *file_name, int append)
{
	int		prelen;
	int		i;
	int		j;
	int		error;
	t_list	*node;
	char	**new_env;

	error = 0;
	if (args[1] == NULL)
		error = display_env (env, file_name, append);
	i = 1;
	while (args[i] != NULL)
	{
		if (!valid_varible(args[i]))
		{
			error += print_error(args[i], ": not a valid identifier", 1);
			++i;
			continue ;
		}
		if (ft_strchr(args[i], '=') != 0)
			prelen = ft_strchr(args[i], '=') - args[i];
		else
			prelen = ft_strlen(args[i]);
		j = 0;
		while (env [j] && ft_strncmp_p(env[j], args[i], prelen) != 0)
			++j;
		if (env[j] && ft_strchr(args[i], '=') != 0)
		{
			env[j] = ft_strdup(args[i]); // protect
			node = ft_lstnew(env[j]);
			if (node == 0)
			{
				free(args);
				return (1);
			}
			ft_lstadd_back(&g_m, node);
		}
		else if (!env[j])
		{
			new_env = (char **)malloc(sizeof(*env) * (j + 2));
			node = ft_lstnew(new_env);
			if (node == 0)
			{
				free(args);
				return (1);
			}
			ft_lstadd_back(&g_m, node);
			cpynewenv(new_env, env); // check success
			env[j] = args[i];
			env[j + 1] = NULL;
		}
		++i;
	}
	free(args);
	return (0);
}
*/