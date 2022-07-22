/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:00:21 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/21 19:17:30 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	signal_handler(int signum, siginfo_t *info, void *ptr)
// {
// 	int	status;
// 	int	has_live_child;

// 	(void) info;
// 	(void) ptr;
// 	has_live_child = 1;
// 	if (signum == SIGINT)
// 	{
// 		if (!g_m)
// 			exit(0);
// 		if (waitpid(-1, &status, WNOHANG) == -1)
// 			has_live_child = 0;
// 		if (has_live_child == 0
// 			&& (int) *((int *)(g_m->content)) != getpid())
// 		{
// 			ft_lstclear(&g_m, free);
// 			exit(0);
// 		}
// 	}
// 	if (waitpid(-1, &status, WNOHANG) == -1)
// 	{
// 		//char i = 26;
// 		//write(0, &i, 1);
// 		ft_printf("\r>Enter a string:\n");
// 		rl_redisplay();
// 		rl_on_new_line();
// 		rl_redisplay();
// 		rl_on_new_line();
// 		//rl_replace_line("", 0);
// 		//ft_printf("\n>Enter a string: ");
// 	}
// }

static void	signal_handler(int signum, siginfo_t *info, void *ptr)
{
	(void) info;
	(void) ptr;
	if (waitpid(-1, NULL, WNOHANG) != -1)
		return ;
	if (signum == SIGINT)
	{
		//rl_replace_line("", 0);
		//ft_printf("\r>Enter a string:                               \r");
		//ft_printf("\r");
		//rl_redisplay();
		//ft_putchar_fd(EOF,0);
		//write(0, "\ngreen", 7);
		//write(1, "\ngreen\n", 1);
		//ft_putstr_fd("green", 0);
		//write(0, "\n", 0);
		//int fd = dup(STDIN_FILENO);
		//close(fd);
		//write(1, "green", 6);
		//write(2, "green", 6);
		//char *temp = ft_strdup("g");
		//temp[0] = 4;
		rl_replace_line("", 0);
		ft_putstr_fd("\b\b  \n", 2);
		//rl_redisplay();
		//rl_replace_line("", 0);
		rl_on_new_line();
		//ft_putstr_fd("Enter a string: ", 0);
		rl_redisplay();
		//rl_forced_update_display();
		//free(temp);
		//ft_putstr_fd("\r\n", 2);
		//ft_printf("\n");
	}
	else if (signum == SIGQUIT)
		return ;
}

int	signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	//rl_catch_signals = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return (0);
}
