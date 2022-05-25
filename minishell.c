/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:19:39 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/25 15:00:35 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argv, char **argc, char **env)
{
	t_new	*lst;

	(void)argv;
	(void)argc;
	lst = NULL;
	excute (lst, env);
	// while (*env)
	// {
	// 	ft_printf("%s\n", *env);
	// 	++env;
	// }
}
