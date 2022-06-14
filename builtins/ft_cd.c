/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:25:17 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/08 10:34:18 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_chdir(char *str, char **env)
{
	char *data;
	if (chdir(str) == -1)
	{
		printf("Error \n");
	}
	data = getcwd(NULL, 0);
	export("PWD", data, env);
}