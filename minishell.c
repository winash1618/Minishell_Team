/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:19:39 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/15 16:47:56 by ayassin          ###   ########.fr       */
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
	//char	*str[] = {"cat", "green.txt", "|" ,"grep", "high", "|", "wc", NULL};
	//char	*str[] = {"www", "|", "cat", "|", "ls",  NULL};
	//char	*str[] = {"cat", ">green.txt",  NULL};
	//char	*str[] = {"ls", "|", "cat", ">green.txt",  NULL};
	char	*str[] = {"/bin/cat", "<green.txt", NULL};
	//char	*str[] = {"cat", "|", "cat" , "-n", "|", "ls", NULL};
	//char	*str[] = {"ls", "|", "cat", "<<", "green", ">green.txt", "|", "tail",
	//		 "|", "wc", "-l", "|", "curl", "wttr.in/abudhabi", "|", "wc", NULL};
	// cat <<green >green.txt
	(void)argv;
	(void)argc;
	(void)env;
	// if (access("libft", F_OK) == 0)
	// 	printf("*******\n");
	// if (access("libft", W_OK) == 0)
	// 	printf("!!!!!!!\n");
	// if (open("libft", O_WRONLY) == -1)
	// 	printf("_______\n");
	// else 
	// 	printf("@@@@@@\n");
	lst = temp_makelist(str);
	//lst_print(lst);
	excute (lst, env);
	// if (argv == 2)
	// {
	// 	char *line = line_input(argc[1]);
	// 	free(line);
	// }
	ft_printf("%s green\n%s" , "\033[0;31m", "\033[0m");
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
