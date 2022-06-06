/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:25:17 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/05 17:25:20 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <termcap.h>
#include <readline/readline.h>
#include <string.h>
#include <readline/history.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

void ft_chdir(char *str)
{
	if (chdir(str) == -1)
	{
		printf("Error \n");
	}
}
int main ()
{
	char data[100];
	 printf("%s\n", getcwd(data, 100));
	
	ft_chdir(str);
	
	 printf("%s\n", getcwd(data, 100));
  
	return (0);
}