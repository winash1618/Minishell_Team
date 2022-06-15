/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:25:17 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/06 10:29:28 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_chdir(char *str, char **env)
{
	char data[100];
	if (chdir(str) == -1)
	{
		printf("Error \n");
	}
	export("PWD", getcwd(data, 100), env);
}