/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:19:39 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/26 17:59:24 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*g_m;

int	main(int ac, char **av, char **env)
{
	t_new	*cmd;
	char	*line;
	t_info	*info;
	t_list	*node;
	int		err;

	(void) ac;
	(void) av;
	g_m = NULL;
	node = ft_lstnew(NULL);
	if (node == NULL)
		return (print_error("", "malloc failed", 1));
	ft_lstadd_front(&g_m, node);
	signals();
	info = malloc(sizeof(t_info));
	if (info == NULL)
		cleanexit(NULL, NULL, print_error("", "malloc failed", 1), NULL);
	if (ft_lstadd_backhelper(&g_m, info) != 0)
		cleanexit(NULL, NULL, 1, NULL);
	if (setnewenv(env))
		cleanexit(NULL, NULL, 1, NULL);
	if (update_shlvl(env, "SHLVL"))
		cleanexit(NULL, NULL, 1, NULL);
	info->flag = 1;
	info->e_flag = 0;
	while (1)
	{
		info->e_flag = 0;
		info->q_flag = 0;
		err = errno;
		line = ft_readline();
		if (!errno)
			errno = err;
		if (line)
			add_history(line);
		else
			cleanexit(NULL, NULL, 0, NULL);
		quote_counter(line, info);
		if (!line || !strcmp(line, "exit"))
			cleanexit(NULL, NULL, 0, NULL);
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
	cleanexit(NULL, NULL, 0, NULL);
	return (0);
}
