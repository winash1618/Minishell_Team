/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 07:33:02 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/05/28 16:55:07 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

g_list g_m;
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
	// (void)env;
	// char *buf = (char *)malloc(sizeof(char) * (ft_strlen(getenv("TERM")) + 1));
	t_info *info;
	info = malloc(sizeof(t_info));
	t_new *cmd;
	info->flag = 1;
	info->e_flag = 0;
	t_var *var;
	// char *str;
	// str = NULL;
	// tgetent(buf, getenv("TERM"));
	// str = tgetstr("cl", NULL);
	// free(buf);
	// printf("%s", str);
	// printf(" ");
	char *line;
	int i = 0;
	while (++i < 5)
	{
		info->e_flag = 0;
		info->q_flag = 0;

		line = ft_readline();
		quote_counter(line, info);
		if (!line || !strcmp(line, "exit"))
			return (0);
		else if (!(strcmp(line, "")))
			;
		else if (!strcmp(line, "clear"))
			ft_clearscreen();
		else if (!info->q_flag)
		{
			if(*line && check_var(line, info))
			{
				var_lexer(&var, line);
				lst_print_vars(var);
			}
			else
			{
				normal_lexer(&cmd, info, line);
				find_dollar_presence(cmd);
				dollar_expansion(cmd, env);
				lst_print(cmd);
			}
		}
		free (line);
	}
	free(g_m.lst);
	return(0);
}
