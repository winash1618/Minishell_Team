/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 07:33:02 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/07/25 18:27:18 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *g_m;
// int main(int ac, char **argv, char **env)
// {
// 	ac++;
// 	(void)argv;
// 	char *s = get_expanded_string("a($PATH&$PATH&|a$PATHfsd", env);
// 	// char *s = get_dollar_path("fsd", env);
// 	// int s = get_strlen("aPATH&$PATH&|a");
// 	ft_printf("hi %s\n", s);
// 	// printf("hi");
// }


int main(int ac, char **av, char **env)
{
	ac++;
	(void)av;
	// count_size(env);
	g_m = NULL;
	// t_list *hist;
	// hist = NULL;
	// (void)env;
	// char *buf = (char *)malloc(sizeof(char) * (ft_strlen(getenv("TERM")) + 1));
	// g_m = ft_lstnew((void *)getpid());
	// ft_lstadd_front(g_m)
	t_info *info;
	info = malloc(sizeof(t_info));
	g_m = ft_lstnew((void *)info);
	t_new *cmd;
	info->flag = 1;
	info->e_flag = 0;
	// 
	// t_var *var;
	// char *str;
	// str = NULL;
	// tgetent(buf, getenv("TERM"));
	// str = tgetstr("cl", NULL);
	// free(buf);
	// printf("%s", str);
	// printf(" ");
	char *line;
	int i = 0;
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
			//list clear
			exit(5);
		}
		// if (line && !hist)
		// 	hist = ft_lstnew((void *)line);
		// else if (line)
		// {
		// 	t_list *tmp = ft_lstnew((void *)line);
		// 	ft_lstadd_front(&hist, tmp);
		// }
		quote_counter(line, info);
		if (!line || !strcmp(line, "exit"))
		{
			ft_lstclear(&g_m, free);
			return (0);
		}
		else if (!(strcmp(line, "")))
			;
		else if (!strcmp(line, "clear"))
			ft_clearscreen();
		else if (!info->q_flag)
		{
			// if(*line && check_var(line, info))
			// {
			// 	var_lexer(&var, line);
			// 	lst_print_vars(var);
			// }
			// else
			// {
				normal_lexer(&cmd, info, line);
				lst_print(cmd);
				printf("\n********* Befor Dollar Expansion *********************\n");
				find_dollar_presence(cmd);
				find_redirection_presence(cmd);
				dollar_expansion(cmd, env);
				lst_print(cmd);
				printf("\n************* After Dollar Expansion *****************\n");
				make_all_zero(cmd);
				if (cmd && !syntax_error(cmd))
				{
					make_big_list(&cmd);
					lst_print(cmd);
					printf("\n************* After Make big list *****************\n");
					ft_lst_join(cmd);
					lst_print(cmd);
					printf("\n****************After list join **************\n");
					find_redirection_presence(cmd);
					lst_print(cmd);
					printf("\n************After finding redirection presence ******************\n");
					// excute (cmd, env);
				}
			// }
		}
		free (line);
	}
	ft_lstclear(&g_m, free);
	return(0);
}

// int main(int ac, char **av, char **env)
// {
// 	ac++;
// 	(void)av;
// 	// count_size(env);
// 	g_m = NULL;
// 	// t_list *hist;
// 	// hist = NULL;
// 	// (void)env;
// 	// char *buf = (char *)malloc(sizeof(char) * (ft_strlen(getenv("TERM")) + 1));
// 	// g_m = ft_lstnew((void *)getpid());
// 	// ft_lstadd_front(g_m)
// 	t_info *info;
// 	info = malloc(sizeof(t_info));
// 	g_m = ft_lstnew((void *)info);
// 	t_new *cmd;
// 	info->flag = 1;
// 	info->e_flag = 0;
// 	// 
// 	// t_var *var;
// 	// char *str;
// 	// str = NULL;
// 	// tgetent(buf, getenv("TERM"));
// 	// str = tgetstr("cl", NULL);
// 	// free(buf);
// 	// printf("%s", str);
// 	// printf(" ");
// 	char *line;
// 	int i = 0;
// 	while (1)
// 	{
// 		i++;
// 		info->e_flag = 0;
// 		info->q_flag = 0;
		
// 		line = ft_readline();
// 		if (line)
// 			add_history(line);
// 		else
// 		{
// 			//list clear
// 			exit(5);
// 		}
// 		// if (line && !hist)
// 		// 	hist = ft_lstnew((void *)line);
// 		// else if (line)
// 		// {
// 		// 	t_list *tmp = ft_lstnew((void *)line);
// 		// 	ft_lstadd_front(&hist, tmp);
// 		// }
// 		quote_counter(line, info);
// 		if (!line || !strcmp(line, "exit"))
// 		{
// 			ft_lstclear(&g_m, free);
// 			close(0);
// 			close(1);
// 			close(2);
// 			return (0);
// 		}
// 		else if (!(strcmp(line, "")))
// 			;
// 		else if (!strcmp(line, "clear"))
// 			ft_clearscreen();
// 		else if (!info->q_flag)
// 		{
// 			// if(*line && check_var(line, info))
// 			// {
// 			// 	var_lexer(&var, line);
// 			// 	lst_print_vars(var);
// 			// }
// 			// else
// 			// {
// 				normal_lexer(&cmd, info, line);
// 				find_dollar_presence(cmd);
// 				find_redirection_presence(cmd);
// 				dollar_expansion(cmd, env);
// 				make_all_zero(cmd);
// 				if (cmd && !syntax_error(cmd))
// 				{
// 					make_big_list(&cmd);
// 					ft_lst_join(cmd);
// 					find_redirection_presence(cmd);
// 					// excute (cmd, env);
// 				}
// 			// }
// 		}
// 		free (line);
// 	}
// 	ft_lstclear(&g_m, free);
// 	return(0);
// }