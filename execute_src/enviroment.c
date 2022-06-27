/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:44:36 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/26 20:11:27 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cpynewenv(char **new_env, char **env)
{
	int		count;
	t_list	*temp;

	count = 0;
	while (env[count])
	{
		new_env[count] = ft_strdup(env[count]);
		if (new_env[count] == NULL)
			return (1);
		temp = ft_lstnew(new_env[count]);
		if (!temp)
		{
			free (new_env[count]);
			return (1);
		}
		ft_lstadd_back(&g_m, temp);
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

int	ft_export(char **args, char **env)
{
	int		prelen;
	int		i;
	t_list	*node;
	char	**new_env;

	if (args[1] == NULL || ft_strchr(args[1], '=') == NULL)
		return (0);
	prelen = ft_strchr(args[1], '=') - args[1] + 1;
	i = 0;
	while (env [i] && ft_strncmp_p(env[i], args[1], prelen) != 0)
		++i;
	if (env[i])
	{
		env[i] = args[1]; // I do not free env
		node = ft_lstnew(env[i]);
		if (node == 0)
		{
			//free(args);
			return (1);
		}
		ft_lstadd_back(&g_m, node);
	}
	else
	{
		new_env = (char **)malloc(sizeof(*env) * (i + 2));
		cpynewenv(new_env, env); // check success
		env[i] = args[1];
		env[i + 1] = NULL;
	}
	return (0);
}


