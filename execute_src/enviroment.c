/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:44:36 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/02 19:52:12 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cpynewenv(char **new_env, char **env)
{
	int		count;
	t_list	*node;

	count = 0;
	while (env[count])
	{
		new_env[count] = ft_strdup(env[count]);
		if (new_env[count] == NULL)
			return (1);
		node = ft_lstnew(new_env[count]);
		if (!node)
		{
			free (new_env[count]);
			return (1);
		}
		ft_lstadd_back(&g_m, node);
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
	t_list	*temp;

	count = 0;
	new_env = NULL;
	while (env && env[count])
		++count;
	if (count)
		new_env = (char **)malloc((sizeof(*new_env) + 1) * count);
	if (!new_env)
		return (1);
	temp = ft_lstnew(new_env);
	if (!temp)
		return (1);
	ft_lstadd_back(&g_m, temp);
	return (cpynewenv(new_env, env));
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

int	ft_export(char **args, char **env)
{
	int		prelen;
	int		i;
	int		j;
	t_list	*node;
	char	**new_env;

	i = 0;
	if (args[1] == NULL)
	{
		while (env[i])
		{
			ft_printf("declare -x ");
			j = 0;
			while (env[i][j] && env[i][j] != '=')
				write(1, &(env[i][j++]), 1);
			if (env[i][j] == '=')
				ft_printf("=\"%s\"", &(env[i][j + 1]));
			write(1, "\n", 1);
			++i;
		}
		free(args);
		return (0);
	}
	i = 1;
	while (args[i] != NULL)
	{
		if (!valid_varible(args[i]))
		{
			print_error(": not a valid identifier", args[i]);
			++i;
			continue ;
		}
		else
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

int	ft_unset(char **args, char **env)
{
	int		prelen;
	int		i;
	int		j;

	i = 1;
	while (args[i] != NULL)
	{
		if (!ft_isalpha(args[i][0]) || ft_strchr(args[i], '=') != 0)
		{
			print_error(args[i++], ": not a valid identifier");
			continue ;
		}
		prelen = ft_strlen(args[i]) + 1;
		j = 0;
		while (env [j] && !((ft_strncmp_p(env[j], args[i], prelen) == '=')
			|| (ft_strncmp_p(env[j], args[i], prelen) == 0 && ft_strchr(env[j], '=') == NULL)))
			++j;
		while (env[j] && env [j + 1])
		{
			env[j] = env[j + 1];
			++j;
		}
		env[j] = NULL;
		++i;
	}
	free(args);
	return (0);
}
