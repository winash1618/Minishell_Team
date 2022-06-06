/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:19:17 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/06 17:56:59 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Retun a string since the first occurnce of string "needle" 
in the string "haystack" within "len" chars of "haystack"*/

/* Compare the first "n" chars from strings "s1" & "s2".
Return the diffrence in the first char or 0 if no diffrence is found
**NOT PROTECTED VS NULL INPUT**/
int	ft_strncmp_protected(const char *s1, const char *s2, size_t n)
{
	size_t	pos;

	pos = 0;
	if (!n || !s1 || !s2)
		return (0);
	while (pos < (n - 1) && s1[pos] && s2[pos] && (unsigned char)s1[pos]
		== (unsigned char)s2[pos])
		pos++;
	return ((unsigned char)s1[pos] - (unsigned char)s2[pos]);
}

char	*line_input(char *delimiter)
{
	char	*line;
	char	*one_line;

	line = NULL;
	one_line = NULL;
	while (1)
	{
		one_line = readline("> ");
		if (ft_strncmp_protected(one_line, delimiter \
			, ft_strlen(delimiter) + 1) != 0)
		{
			ft_strjoin_minishell(&line, one_line);
			ft_strjoin_minishell(&line, "\n");
			free(one_line);
		}
		else
			break ;
	}
	free(one_line);
	return (line);
}

void	skip_node(t_new **lst, int *skip_flag)
{
	*skip_flag = 1;
	if (!(lst && *lst))
	{
		ft_printf("what are you doing");
		exit(-1);
	}
	if ((*lst)->prev != NULL)
		(*lst)->prev->next = (*lst)->next;
	if ((*lst)->next != NULL)
		(*lst)->next->prev = (*lst)->prev;
	*lst = (*lst)->next;
}

char	*redirect_input(t_new **lst, int *skip_flag)
{
	char	*in_file_name;
	t_new	*temp;

	in_file_name = NULL;
	temp = *lst;
	if (temp && *(temp->token) == '<' && *((temp->token) + 1) != '<') // use flag
	{
		if (*((temp->token) + 1) != '\0')
			in_file_name = (temp->token) + 1;
		else if (temp->next)
		{
			in_file_name = temp->next->token;
			skip_node(&temp, skip_flag);
		}
		else
			ft_printf("parse error near \\n");
		skip_node(&temp, skip_flag);
	}
	*lst = temp;
	return (in_file_name);
}

int	empty_file(char *file_name)
{
	int	fd;

	if (access(file_name, F_OK) == 0)
	{
		if (access(file_name, W_OK) == 0)
		{
			fd = open(file_name, O_TRUNC);
			close(fd);
		}
		else
			return (-1); // this is an error you should handel
	}
	else
	{
		fd = open(file_name, O_CREAT | O_TRUNC, 0644);
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
		ft_printf("parse error near \n");
	skip_node(&temp, skip_flag);
	*lst = temp;
	if (*append_flag == 0 || access(out_file_name, F_OK) == -1)
		empty_file(out_file_name); //handel error
	return (out_file_name);
}