/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:38:44 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/17 15:50:01 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	child_manager(t_new *lst, int (*fd)[2], int child_num)
{
	char	*in_file_name;
	char	*out_file_name;
	int		in_file_fd;
	int		out_file_fd;

	in_file_fd = NULL;
	if (child_num > 0)
		set_(&lst, &in_file_name, fd[child_num][1]);
	else
		set_pipes(&lst, STDIN_FILENO, fd[child_num][1]);
	hijack_stdin(in_file, in_file_name);
	hijack_stdout(out_file, out_file_name,
		*append_or_input_flag, list_has_pipes(*lst));
}
