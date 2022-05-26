/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:19:39 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/26 10:22:39 by ayassin          ###   ########.fr       */
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
	// 	if(ft_strnstr(*env, "LOGNAME", ft_strlen("LOGNAME")))
	// 		ft_printf("%s\n", *env);
	// 	++env;
	// }
}
