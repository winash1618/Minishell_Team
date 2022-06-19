/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 09:00:21 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/18 18:03:09 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	signal_handler(int signum, siginfo_t *info, void *ptr)
{
	int	i;
	int	status;
	int	has_live_child;

	i = 0;
	has_live_child = 1;
	if (signum == SIGINT)
	{
		if (!g_m)
			return ;
		while (i < 100)
		{
			if (waitpid(-1, &status, WNOHANG) == -1)
			{
				has_live_child = 0;
				break ;
			}
			usleep (100);
		}
		if (has_live_child == 0 && (int) *((int *)(g_m->content)) != getpid())
		{
			//ft_lstclear(g_m, free());
			exit(0);
		}
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