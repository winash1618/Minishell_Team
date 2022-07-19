/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:19:39 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/19 10:07:39 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*g_m;

/*atoi function with a flag "valid flag" to check if resulting int is positive
and has non-numeric digits*/
int	minishell_atoi(char *str, int *flag)
{
	int				i;
	int				sign;
	unsigned long	num;

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
		(*flag) = 1;
	while (str[i] >= '0' && str[i] <= '9' && !(*flag))
	{
		num = num * 10 + str[i] - '0';
		if ((num >> 31) && !(sign == -1 && ((num - 1) >> 31 == 0)))
			*flag = 1;
		++i;
	}
	return (num * sign);
}

int	update_shlvl(char **env, char *var)
{
	int		i;
	int		error;
	int		level;
	int		len;
	char	*temp;

	i = 0;
	error = 0;
	len = ft_strlen(var);
	while (env [i] && !(ft_strncmp_p(env[i], var, len) == 0
			&& (env[i][len] == '\0' || env[i][len] == '=')))
			++i;
	if (env[i])
	{
		level = minishell_atoi(&(env[i][5 + (ft_strchr(env[i], '=') != 0)]), &error);
		//ft_printf("The number is %d for string %s	%s\n", level, );
		if (error || level == 999)
			append_env(env, "SHLVL=", i);
		else if (level < 0)
			append_env(env, "SHLVL=0", i);
		else if (level > 999)
		{
			print_error(" :warning", ": shell level too high, resetting to 1\n", 1);
			append_env(env, "SHLVL=1", i);
		}
		else
		{
			temp = ft_strdup("SHLVL=");
			ft_strjoin_ms(&temp, ft_itoa(level + 1));
			append_env(env, temp, i);
			free (temp);
		}
	}
	else
	{
		error = append_env(env, "SHLVL=1", i);
	}
	return (error);
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
		return (1);
	if (ft_lstadd_backhelper(&g_m, info) != 0)
	{
		ft_lstclear(&g_m, free);
		return (1);
	}
	if (setnewenv(env))
	{
		ft_lstclear(&g_m, free);
		//free (env);
		return (1);
	}
	//update_shlvl(env, "SHLVL");
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
			exit (0);
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
