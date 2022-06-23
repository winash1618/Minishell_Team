/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:19:17 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/21 08:58:28 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_node(t_new **lst, int *skip_flag)
{
	*skip_flag = 1;
	if (!(lst && *lst))
	{
		ft_putstr_fd("What are you doing, there is no list\n", 2);
		exit(-1);
	}
	if ((*lst)->prev != NULL)
		(*lst)->prev->next = (*lst)->next;
	if ((*lst)->next != NULL)
		(*lst)->next->prev = (*lst)->prev;
	*lst = (*lst)->next;
}

int	input_file_check(char *file_name)
{
	int	fd;

	if (access(file_name, F_OK) == 0)
	{
		if (access(file_name, R_OK) == 0)
		{
			fd = open(file_name, O_RDONLY);
			if (fd == -1)
				return (print_error(file_name, ": Failed to open"));
			else if (read(fd, file_name, 0) == -1)
			{
				close (fd);
				return (print_error(file_name, ": Is a directory"));
			}
			close(fd);
		}
		else
			return (print_error(file_name, ": Permission denied"));
	}
	else
		return (print_error(file_name, ": No such file or directory"));
	return (0);
}

char	*redirect_input(t_new **lst, int *skip_flag, int *input_flag)
{
	char	*in_file_name; //not an accurate name
	t_new	*temp;

	in_file_name = NULL;
	temp = *lst;
	*input_flag = 0;
	if (temp && *((temp->token) + 1) == '<')
		*input_flag = 1;
	if (temp)
	{
		if (*((temp->token) + 1 + *input_flag) != '\0')
			in_file_name = (temp->token) + 1 + *input_flag;
		else if (temp->next)
		{
			in_file_name = temp->next->token;
			skip_node(&temp, skip_flag);
		}
		else
			print_error("syntax error near unexpected token ", temp->token);
		skip_node(&temp, skip_flag);
	}
	if ((*input_flag == 0) && input_file_check(in_file_name) == -1)
		return (NULL);
	*lst = temp;
	return (in_file_name);
}

int	output_file_check(char *file_name, int trunc)
{
	int	fd;

	trunc = (trunc != 0) * O_TRUNC;
	if (access(file_name, F_OK) == 0)
	{
		if (access(file_name, W_OK) == 0)
		{
			fd = open(file_name, O_WRONLY | trunc);
			if (fd == -1)
				return (print_error(file_name, ": Is a directory"));
			close(fd);
		}
		else
			return (print_error(file_name, ": Permission denied"));
	}
	else
	{
		fd = open(file_name, O_CREAT, 0644);
		if (fd == -1)
			return (print_error(file_name, ": File failed to creat"));
		close (fd);
	}
	return (0);
}

char	*redirect_output(t_new **lst, int *skip_flag, int *append_flag)
{
	char	*out_file_name;
	t_new	*temp;

	out_file_name = NULL;
	temp = *lst;
	if (*((temp->token) + 1) == '>') // use flag
		*append_flag = 1;
	else
		*append_flag = 0;
	if (*((temp->token) + 1 + *append_flag) != '\0')
		out_file_name = (temp->token) + 1 + *append_flag;
	else if (temp->next)
	{
		out_file_name = temp->next->token;
		skip_node(&temp, skip_flag);
	}
	else
		print_error("syntax error near unexpected token ", temp->token);
	skip_node(&temp, skip_flag);
	*lst = temp;
	if (output_file_check(out_file_name, (*append_flag == 0)) == -1)
		return (NULL);
	return (out_file_name);
}
