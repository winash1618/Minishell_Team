/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:55:02 by mkaruvan          #+#    #+#             */
/*   Updated: 2022/06/19 16:29:46 by mkaruvan         ###   ########.fr       */
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
	printf("");
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