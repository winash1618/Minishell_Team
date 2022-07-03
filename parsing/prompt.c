/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:55:02 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/07/02 17:41:22 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_readline(void)
{
	char	*line;

	line = readline(">Enter a string: ");
	return (line);
}

void	ft_clearscreen(void)
{
	char	*buf;
	char	*str;
	t_list	*tmp;

	buf = (char *)malloc(sizeof(char) * (ft_strlen(getenv("TERM")) + 1));
	tmp = ft_lstnew((void *)buf);
	ft_lstadd_back(&g_m, tmp);
	tgetent(buf, getenv("TERM"));
	str = tgetstr("cl", NULL);
	printf("%s", str);
	// printf("");
}

// void	ft_clearscreen(void)
// {
// 	// char	*buf;
// 	char	*str;

// 	// buf = (char *)malloc(sizeof(char) * (ft_strlen(getenv("TERM")) + 1));
// 	// g_m = ft_lstnew((void *)buf);
// 	tgetent(buf, getenv("TERM"));
// 	str = tgetstr("cl", NULL);
// 	printf("%s", str);
// 	// printf("");
// }

// for printing purposes
void	lst_print(t_new *pars)
{
	while (pars != NULL)
	{
		printf("<token: %s> <flag: %d> <d_flag: %d> <s_flag: %d> <l_flag: %d> <l2_flag: %d> <r_flag: %d> <r2_flag: %d> <dq_flag: %d>",
			pars->token, pars->flag, pars->d_flag, pars->s_flag, pars->l_flag, 
			pars->l2_flag, pars->r_flag, pars->r2_flag, pars->dq_flag);
		printf("\n");
		pars = pars->next;
	}
}

void	lst_rev_print(t_new *pars)
{
	while (pars && pars->next != NULL)
		pars = pars->next;
	while (pars != NULL)
	{
		printf("<token: %s> <flag: %d> <d_flag: %d> ",
			pars->token, pars->flag, pars->d_flag);
		printf("\n");
		pars = pars->prev;
	}
}
// control - v then enter, gives ^M 