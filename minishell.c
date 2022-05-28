/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:19:39 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/28 16:37:13 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_new	*temp_makelist(char **str)
{
	t_new	*commands;
	int i = 0;

	commands = NULL;
	while (str[i])
	{
		temp_lstadd_back(&commands, temp_lst_newnode(str[i]));
		++i;
	}
	return (commands);
}

int	main(int argv, char **argc, char **env)
{
	t_new	*lst;
	char	*str[] = {"echo", "42\n", "|" ,"wc", "-l", NULL};

	(void)argv;
	(void)argc;
	(void)env;
	lst = temp_makelist(str);
	lst_print(lst);
	excute (lst, env);
	// while (*env)
	// {
	// 	if(ft_strnstr(*env, "LOGNAME", ft_strlen("LOGNAME")))
	// 		ft_printf("%s\n", *env);
	// 	++env;
	// }
}
