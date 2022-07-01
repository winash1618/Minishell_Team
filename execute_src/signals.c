/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:00:21 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/30 18:25:23 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	signal_handler(int signum, siginfo_t *info, void *ptr)
{
	int	status;
	int	has_live_child;

	(void) info;
	(void) ptr;
	has_live_child = 1;
	if (signum == SIGINT)
	{
		if (!g_m)
			exit(0);
		if (waitpid(-1, &status, WNOHANG) == -1)
			has_live_child = 0;
		if (has_live_child == 0
			&& (int) *((int *)(g_m->content)) != getpid())
		{
			ft_lstclear(&g_m, free);
			exit(0);
		}
	}
	if (waitpid(-1, &status, WNOHANG) == -1)
	{
		//char i = 26;
		//write(0, &i, 1);
		ft_printf("\r>Enter a string:\n");
		rl_redisplay();
		rl_on_new_line();
		rl_redisplay();
		rl_on_new_line();
		//rl_replace_line("", 0);
		//ft_printf("\n>Enter a string: ");
	}
}
	// if (signum == SIGQUIT) 
	// 	; //do nothing

int	signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return (0);
}
