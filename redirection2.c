/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:54:00 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/06 15:03:14 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hijack_stdin(int in_file, char *in_file_name) //handel errors
{
	if (in_file_name != NULL)
		in_file = open(in_file_name, O_RDONLY);
	dup2(in_file, STDIN_FILENO);
	return (0);
}

int	hijack_stdout(int out_file, char *out_file_name, int append_flag, int flag) //handle errors
{
	append_flag = (O_APPEND * (append_flag)) | (O_TRUNC * (!append_flag));
	if (out_file_name != NULL)
		out_file = open(out_file_name, O_WRONLY | O_CREAT | append_flag);
	if (flag || out_file_name != NULL) 
		dup2(out_file, STDOUT_FILENO);
	return (0);
}

int	redirection_loop(t_new **lst, char **in_file_name, char **out_file_name, int *append_flag)
{
	t_new	*temp;
	int		skip_flag;

	temp = *lst;
	skip_flag = 0;
	while (temp && *(temp->token) != '|') //use flag
	{
		if (temp && *(temp->token) == '<') // and flag
			*in_file_name = redirect_input(&temp, &skip_flag);
		if (temp && *(temp->token) == '>') // and flag
			*out_file_name = redirect_output(&temp, &skip_flag, append_flag);
		if (skip_flag == 1)
			skip_flag = 0;
		else
			temp = temp->next;
	}
	if (temp != NULL)
		temp->next = NULL; // remeber to free the list for the child
	while (*lst && ft_strchr("<>", *((*lst)->token))) // check flags (and free)
		*lst = (*lst)->next;
	return (0);
}

t_new	**set_pipes(t_new **lst, int in_file, int out_file)
{
	char	*in_file_name;
	char	*out_file_name;
	int		append_flag;
	t_new	*temp;

	in_file_name = NULL;
	out_file_name = NULL;
	append_flag = 0;
	temp = *lst;
	if (*(temp->token) == '|') // use flag
		ft_printf("DUCK");
	redirection_loop(lst, &in_file_name, &out_file_name, &append_flag);
	hijack_stdin(in_file, in_file_name);
	hijack_stdout(out_file, out_file_name, append_flag, list_has_pipes(*lst));
	return (lst);
}