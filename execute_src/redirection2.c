/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:54:00 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/13 12:12:03 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	hijack_stdin(int in_file, char *in_file_name) //handel errors
{
	if (in_file_name != NULL)
	{
		if (access(in_file_name, F_OK) == -1 || access(in_file_name, R_OK) == -1)
			return (-1);
		in_file = open(in_file_name, O_RDONLY);
		if (in_file == -1)
			return (-1);
	}
	if (in_file == STDIN_FILENO)
		return (0);
	if (dup2(in_file, STDIN_FILENO) == -1)
	{
		if (in_file_name != NULL)
			close (in_file);
		return (-1);
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
			return (-1);
		else
			out_file = open(out_file_name, O_WRONLY | append_flag);
		if (out_file == -1)
			return (-1);
	}
	if (flag || out_file_name != NULL)
	{
		if (out_file == STDIN_FILENO)
			return (0);
		if (dup2(out_file, STDOUT_FILENO))
		{
			if (out_file_name != NULL)
				close (out_file);
			return (-1);
		}
	}
	return (0);
}

int	redirection_loop(t_new **lst, char **in_file_name, char **out_file_name, int *append_flag)
{
	t_new	*temp;
	int		skip_flag;
	char	*user_input;

	temp = *lst;
	skip_flag = 0;
	user_input = NULL;
	while (temp && *(temp->token) != '|') //use flag
	{
		if (temp && *(temp->token) == '<') // and flag
			*in_file_name = redirect_input(&temp, &skip_flag, &user_input);
		if (temp && *(temp->token) == '>') // and flag
			*out_file_name = redirect_output(&temp, &skip_flag, append_flag);
		if (skip_flag == 1)
			skip_flag = 0;
		else
			temp = temp->next;
	}
	if (user_input != NULL)
	{
		*in_file_name = NULL;
		*in_file_name = user_input;
		append_flag[1] = 1;
	}
	if (temp != NULL)
		temp->next = NULL; // remeber to free the list for the child
	while (*lst && ft_strchr("<>", *((*lst)->token))) // check flags (and free)
		*lst = (*lst)->next;
	return (0);
}

void	adopted_child(int in_file, char *here_doc)
{
	int	*fd;

	fd = (int *)malloc(sizeof(*fd) * 2); // add to big list
	pipe(fd);
	ft_putstr_fd(here_doc, fd[1]);
	hijack_stdin(fd[0], NULL);
	close(fd[0]);
	close(in_file);
	close(fd[1]);
}

t_new	**set_pipes(t_new **lst, int in_file, int out_file)
{
	char	*in_file_name;
	char	*out_file_name;
	int		append_or_input_flag[2];
	t_new	*temp;

	in_file_name = NULL;
	out_file_name = NULL;
	append_or_input_flag[0] = 0;
	append_or_input_flag[1] = 0;
	temp = *lst;
	if (*(temp->token) == '|') // use flag
		ft_printf("DUCK");
	redirection_loop(lst, &in_file_name, &out_file_name, append_or_input_flag);
	hijack_stdout(out_file, out_file_name, *append_or_input_flag, list_has_pipes(*lst));
	if (append_or_input_flag[1] == 0)
		hijack_stdin(in_file, in_file_name);
	else
		adopted_child(in_file, in_file_name);
	return (lst);
}
