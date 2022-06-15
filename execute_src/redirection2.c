/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:54:00 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/15 18:08:16 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	hijack_stdin(int in_file, char *in_file_name) //handel errors
{
	if (in_file_name != NULL)
	{
		if (access(in_file_name, F_OK) == -1)
			return (print_error(in_file_name, ": No such file or directory"));
		else if (access(in_file_name, R_OK) == -1)
			return (print_error(in_file_name, ": Permission denied"));
		in_file = open(in_file_name, O_RDONLY);
		if (in_file == -1)
			return (print_error(in_file_name, ": File failed to open"));
	}
	if (in_file == STDIN_FILENO)
		return (0);
	if (dup2(in_file, STDIN_FILENO) == -1)
	{
		if (in_file_name != NULL)
			close (in_file);
		return (print_error(NULL, ": Failed to hijack stdin"));
	}
	return (0);
}

int	hijack_stdout(int out_file, char *out_file_name, int append_flag, int flag) //handle errors
{
	append_flag = (O_APPEND * (append_flag)) | (O_TRUNC * (!append_flag));
	if (out_file_name != NULL)
	{
		if (access(out_file_name, F_OK) == -1)
			out_file = open(out_file_name, O_CREAT, 0644);
		else if (access(out_file_name, W_OK) == -1)
			return (print_error(out_file_name, ": Permission denied"));
		else
			out_file = open(out_file_name, O_WRONLY | append_flag);
		if (out_file == -1)
			return (print_error(out_file_name, ": File failed to open"));
	}
	if (flag || out_file_name != NULL)
	{
		if (out_file == STDIN_FILENO)
			return (0);
		if (dup2(out_file, STDOUT_FILENO) == -1)
		{
			if (out_file_name != NULL)
				close (out_file);
			return (print_error(NULL, ": Failed to hijack stdout"));
		}
	}
	return (0);
}

int	redirection_loop(t_new **lst, char **in_file_name, char **out_file_name, int *append_flag)
{
	t_new	*temp;
	int		skip_flag;

	temp = *lst;
	while (temp && *(temp->token) != '|') //use flag
	{
		skip_flag = 0;
		if (temp && *(temp->token) == '<') // and flag
		{
			*in_file_name = redirect_input(&temp, &skip_flag, &(append_flag[1]));
			if (*in_file_name == NULL)
				return (-1);
		}
		if (temp && *(temp->token) == '>') // and flag
		{
			*out_file_name = redirect_output(&temp, &skip_flag, append_flag);
			if (*out_file_name == NULL)
				return (-1);
		}
		if (skip_flag != 1)
			temp = temp->next;
	}
	if (temp != NULL)
		temp->next = NULL; // remeber to free the list for the child
	while (*lst && ft_strchr("<>", *((*lst)->token))) // check flags (and free)
		*lst = (*lst)->next;
	return (0);
}

int	adopted_child(int in_file, char *here_doc) // handel errors
{
	int	*fd;

	fd = (int *)malloc(sizeof(*fd) * 2); // add to big list
	pipe(fd);
	ft_putstr_fd(here_doc, fd[1]);
	hijack_stdin(fd[0], NULL);
	close(fd[0]);
	close(in_file);
	close(fd[1]);
	return (0); // not always
}

int	set_pipes(t_new **lst, int in_file, int out_file)
{
	char	*in_file_name;
	char	*out_file_name;
	int		append_or_input_flag[2];

	in_file_name = NULL;
	out_file_name = NULL;
	append_or_input_flag[0] = 0;
	append_or_input_flag[1] = 0;
	if (*((*lst)->token) == '|') // use flag
		print_error("syntax error near unexpected token ", (*lst)->token);
	if (redirection_loop(lst, &in_file_name, &out_file_name, append_or_input_flag) == -1)
		return (0);
	if (hijack_stdout(out_file, out_file_name, *append_or_input_flag, list_has_pipes(*lst)) == -1)
		return (-1);
	if (append_or_input_flag[1] == 0)
	{
		if (hijack_stdin(in_file, in_file_name) == -1)
			return (-1);
	}
	else
	{
		if (adopted_child(in_file, in_file_name) == -1)
			return (-1);
	}
	return (0);
}
