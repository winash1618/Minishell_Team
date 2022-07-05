/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:19:39 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/05 19:32:17 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*g_m;

t_new	*temp_makelist(char **str)
{
	t_new	*commands;
	int	i = 0;

	commands = NULL;
	while (str[i])
	{
		temp_lstadd_back(&commands, temp_lst_newnode(str[i]));
		++i;
	}
	return (commands);
}

int	main(int ac, char **av, char **env)
{
	int		*id;
	t_new	*cmd;
	char	*line;
	int		i;
	t_info	*info;

	(void) ac;
	(void) av;
	g_m = NULL;
	signals();
	id = malloc(sizeof(int));
	*id = getpid();
	g_m = ft_lstnew(id);
	info = malloc(sizeof(t_info));
	ft_lstadd_back(&g_m, ft_lstnew((void *)info));
	setnewenv(env);
	info->flag = 1;
	info->e_flag = 0;
	i = 0;
	while (1)
	{
		i++;
		info->e_flag = 0;
		info->q_flag = 0;
		line = ft_readline();
		if (line)
			add_history(line);
		else
		{
			ft_lstclear (&g_m, free);
			exit(0);
		}
		quote_counter(line, info);
		if (!line || !strcmp(line, "exit"))
		{
			ft_lstclear (&g_m, free);
			return (0);
		}
		else if (!(strcmp(line, "")))
			;
		else if (!strcmp(line, "clear"))
			ft_clearscreen();
		else if (!info->q_flag)
		{
			normal_lexer(&cmd, info, line);
			find_dollar_presence(cmd);
			find_redirection_presence(cmd);
			dollar_expansion(cmd, env);
			make_all_zero(cmd);
			if (cmd && !syntax_error(cmd))
			{
				make_big_list(&cmd);
				ft_lst_join(cmd);
				find_redirection_presence(cmd);
				excute (cmd, env);
			}
		}
		free (line);
	}
	ft_lstclear(&g_m, free);
	return (0);
}

// int	main(int argv, char **argc, char **env)
// {
// 	t_new	*lst;
// 	//char	*str[] = {"cat", "green.txt", "|" ,"grep", "high", "|", "wc", NULL};
// 	//char	*str[] = {"cat", "|", "ls",  NULL};
// 	//char	*str[] = {"ls",  NULL};
// 	//char	*str[] = {"ls", "|", "cat", ">green.txt",  NULL};
// 	//char	*str[] = {"/bin/cat", "<green.txt", NULL};
// 	char	*str[] = {"cat", "|", "cat", "|", "ls", NULL};
// 	//char	*str[] = {"ls", "|", "cat", "<<", "green", ">>green.txt", "|", "tail",
// 	//		 "|", "wc", "-l", "|", "curl", "wttr.in/abudhabi", "|", "wc", NULL};
// 	// cat <<green >green.txt
// 	(void)argv;
// 	(void)argc;
// 	(void)env;
// 	// if (access("libft", F_OK) == 0)
// 	// 	printf("*******\n");
// 	// if (access("libft", W_OK) == 0)
// 	// 	printf("!!!!!!!\n");
// 	// if (open("libft", O_WRONLY) == -1)
// 	// 	printf("_______\n");
// 	// else 
// 	// 	printf("@@@@@@\n");
// 	signals();
// 	lst = temp_makelist(str);
// 	//lst_print(lst);
// 	excute (lst, env);
// 	// if (argv == 2)
// 	// {
// 	// 	char *line = line_input(argc[1]);
// 	// 	free(line);
// 	// }
// 	ft_printf("%s green\n%s" , "\033[0;31m", "\033[0m");
// 	temp_list_clear(&lst);
// 	// while (*env)
// 	// {
// 	// 	// if(ft_strnstr(*env, "LOGNAME", ft_strlen("LOGNAME")))
// 	// 		ft_printf("%s\n", *env);
// 	// 	++env;
// 	// }
// }
