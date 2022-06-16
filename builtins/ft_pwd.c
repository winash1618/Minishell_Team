/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:25:42 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/08 10:17:56 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_pwd(char *str, int fd, char **env)
{
	char *data = getcwd(NULL, 0);
	ft_putstr_fd(data, fd); 
	// ft_export("PWD", data, env);
	free(data);
	// ft_export("PWD", getcwd(data, NULL), env);
}