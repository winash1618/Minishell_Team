/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:54:00 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/08 14:07:32 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	hijack_stdin(int in_file, char *in_file_name)
{
	if (in_file_name != NULL)
	{
		if (access(in_file_name, F_OK) == -1)
			return (print_error(in_file_name, ": No such file or directory", 1));
		else if (access(in_file_name, R_OK) == -1)
			return (print_error(in_file_name, ": Permission denied", 1));
		in_file = open(in_file_name, O_RDONLY);
		if (in_file == -1)
			return (print_error(in_file_name, ": File failed to open", 1));
	}
	if (in_file == STDIN_FILENO)
		return (0);
	if (dup2(in_file, STDIN_FILENO) == -1)
	{
		if (in_file_name != NULL)
			close (in_file);
		return (print_error(NULL, ": Failed to hijack stdin", 1));
	}
	return (0);
}

int	hijack_stdout(int out_file, char *out_file_name, int append_flag, int flag)
{
	append_flag = (O_APPEND * (append_flag)) | (O_TRUNC * (!append_flag));
	if (out_file_name != NULL)
	{
		if (access(out_file_name, F_OK) == -1)
			out_file = open(out_file_name, O_CREAT, 0644);
		else if (access(out_file_name, W_OK) == -1)
			return (print_error(out_file_name, ": Permission denied", 1));
		else
			out_file = open(out_file_name, O_WRONLY | append_flag);
		if (out_file == -1)
			return (print_error(out_file_name, ": File failed to open", 1));
	}
	if (flag || out_file_name != NULL)
	{
		if (out_file == STDIN_FILENO)
			return (0);
		if (dup2(out_file, STDOUT_FILENO) == -1)
		{
			if (out_file_name != NULL)
				close (out_file);
			return (print_error(NULL, ": Failed to hijack stdout", 1));
		}
	}
	return (0);
}

int	redirection_loop(t_new **lst, char **in_file_name, char **out_file_name, int *append_flag)
{
	t_new	*temp;
	int		skpflag;
	int		no;

	temp = *lst;
	no = 0;
	while (temp && *(temp->token) != '|') //use flag
	{
		skpflag = 0;
		if (temp && *(temp->token) == '<') // and flag
		{
			no = redirect_input(&temp, &skpflag, &(append_flag[1]), in_file_name);
			if (no)
				return (no);
		}
		if (temp && *(temp->token) == '>') // and flag
		{
			no = redirect_output(&temp, &skpflag, append_flag, out_file_name);
			if (no)
				return (no);
		}
		if (skpflag != 1)
			temp = temp->next;
	}
	if (temp != NULL)
		temp->next = NULL;
	while (*lst && ft_strchr("<>", *((*lst)->token))) // the strchr problem
	{
		*lst = (*lst)->next;
		if (*lst)
			*lst = (*lst)->next;
	}
	return (0);
}

int	adopted_child(int in_file, char *here_doc)
{
	int	*fd;

	fd = (int *)malloc(sizeof(*fd) * 2);
	//ft_lstadd_back(&g_m, ft_lstnew(fd)); // handel error
	if (ft_lstadd_backhelper(fd))
		return (1);
	if (fd == NULL)
		return (1);
	if (pipe(fd))
		return (1);
	ft_putstr_fd(here_doc, fd[1]);
	if (hijack_stdin(fd[0], NULL))
		return (1);
	close(fd[0]);
	if (in_file != STDIN_FILENO)
		close(in_file);
	close(fd[1]);
	return (0);
}

int	set_pipes(t_new **lst, int in_fd, int out_fd)
{
	char	*ifile_name;
	char	*ofile_name;
	int		add_in_f[2];

	ifile_name = NULL;
	ofile_name = NULL;
	add_in_f[0] = 0;
	add_in_f[1] = 0;
	if (*((*lst)->token) == '|') // use flag
		return (print_error("syntax error near unexpected token ", (*lst)->token, 1));
	if (redirection_loop(lst, &ifile_name, &ofile_name, add_in_f))
		return (1);
	if (*lst == NULL || *((*lst)->token) == '|')
		return (1); // this should not be an error
	if (hijack_stdout(out_fd, ofile_name, *add_in_f, list_has_pipes(*lst)))
		return (1);
	if (add_in_f[1] == 0)
	{
		if (hijack_stdin(in_fd, ifile_name))
			return (1);
	}
	else
	{
		if (adopted_child(in_fd, ifile_name))
			return (1);
	}
	return (0);
}
