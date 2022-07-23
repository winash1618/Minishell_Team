/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:00:21 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/23 11:59:25 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	signal_handler(int signum, siginfo_t *info, void *ptr)
{
	(void) info;
	(void) ptr;
	if (waitpid(-1, NULL, WNOHANG) != -1)
		return ;
	if (signum == SIGINT)
	{
		if (g_m->content != NULL)
			cleanexit(NULL, NULL, 5, g_m->content);
		rl_replace_line("", 0);
		ft_putstr_fd("\b\b  \n", 2);
		rl_on_new_line();
		rl_redisplay();
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
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	return (0);
}
