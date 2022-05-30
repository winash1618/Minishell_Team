/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:19:39 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/30 21:27:46 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*g_m;

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
	//char	*str[] = {"cat", "green.txt", "|" ,"grep", "typedef", "|", "wc", "-l", NULL};
	char	*str[] = {"cat", "green.txt", "|" ,"wc", "-l", "|", "wc", NULL};

	(void)argv;
	(void)argc;
	(void)env;
	lst = temp_makelist(str);
	lst_print(lst);
	excute (lst, env);
	printf("green\n");
	temp_list_clear(&lst);
	// while (*env)
	// {
	// 	// if(ft_strnstr(*env, "LOGNAME", ft_strlen("LOGNAME")))
	// 		ft_printf("%s\n", *env);
	// 	++env;
	// }
}

// int main()
// {
// 	int		i;
// 	int		id;
// 	int		fd[2];
// 	int		fd_default[2];

// 	i = 0;
// 	id = 0;
// 	if (pipe(fd) == -1)
// 		return (-1);
// 	if (pipe(fd_default) == -1)
// 		return (-1);
// 	fd_default[0] = dup(STDIN_FILENO);
// 	fd_default[1] = dup(STDOUT_FILENO);
// 	write(1, "high water1\n", 12);
// 	// dup2(fd[1], STDOUT_FILENO);
// 	write(1, "high water\n", 12);
// 	dup2(fd[1], fd_default[1]);
// 	write(1, "high water\n", 12);
// 	close(fd[0]);
// 	close(fd[1]);
// 	close(fd_default[0]);
// 	close(fd_default[1]);
// 	return (0);
// }
