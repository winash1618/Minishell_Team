/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:19:39 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/19 20:47:19 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*g_m;

/*atoi function that overflows ints*/
int	minishell_atoi(char *str)
{
	int	i;
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		++i;
	}
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		++i;
	}
	if (str[i])
		return (0);
	return (num * sign);
}

int	update_shlvlhelper(char **env, int i, int level)
{
	int		error;
	char	*temp;
	char	*temp2;

	error = 0;
	if (level < 0)
			level = 0;
	else if (level > 1000)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putnbr_fd(level, 2);
		ft_putstr_fd(") too high, reseting to 1\n", 2);
		level = 1;
	}
	temp = ft_itoa(level);
	if (temp == NULL)
		return (1);
	temp2 = ft_strjoin("SHLVL=", temp);
	if (temp2 != NULL)
		error = append_env(env, temp2, i);
	free (temp);
	if (temp2 == NULL)
		return (1);
	free(temp2);
	return (error);
}

int	update_shlvl(char **env, char *var)
{
	int		i;
	int		level;
	char	*temp;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (env [i] && !(ft_strncmp_p(env[i], var, len) == 0
			&& (env[i][len] == '\0' || env[i][len] == '=')))
			++i;
	if (env[i])
	{
		level = 1 +
			minishell_atoi(&(env[i][5 + (ft_strchr(env[i], '=') != 0)]));
		if (level == 1000)
			return (append_env(env, "SHLVL=", i));
		return (update_shlvlhelper(env, i, level));
	}
	temp = ft_strdup("SHLVL=1");
	if (temp == NULL)
		return (1);
	return (append_env(env, temp, i));
}

int	main(int ac, char **av, char **env)
{
	t_new	*cmd;
	char	*line;
	int		i;
	t_info	*info;

	(void) ac;
	(void) av;
	g_m = NULL;
	signals();
	info = malloc(sizeof(t_info));
	if (info == NULL)
		cleanexit(NULL, NULL, 1, NULL);
	if (ft_lstadd_backhelper(&g_m, info) != 0)
		cleanexit(NULL, NULL, 1, NULL);
	if (setnewenv(env))
		cleanexit(NULL, NULL, 1, NULL);
	if (update_shlvl(env, "SHLVL"))
		cleanexit(NULL, NULL, 1, NULL);
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

// t_new	*temp_makelist(char **str)
// {
// 	t_new	*commands;
// 	int	i = 0;

// 	commands = NULL;
// 	while (str[i])
// 	{
// 		temp_lstadd_back(&commands, temp_lst_newnode(str[i]));
// 		++i;
// 	}
// 	return (commands);
// }

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
