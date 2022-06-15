/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:25:42 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/06 10:31:22 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_pwd(char *str, int fd, char **env)
{
	char data[100];
	ft_putstr_fd(getcwd(data, 100), fd); 
	export("PWD", getcwd(data, 100), env);
}