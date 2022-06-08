/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:54:00 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/08 14:08:40 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		out_file = open(out_file_name, O_WRONLY | append_flag);
	if (flag || out_file_name != NULL) 
		dup2(out_file, STDOUT_FILENO);
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
	if (append_or_input_flag[1] == 0)
		hijack_stdin(in_file, in_file_name);
	else
	{
		char buff[1] = {'0'};
		while (ft_isprint(buff[0]))
		{
			buff[0] = 0;	
			if (read(in_file, buff, 1) <= 0)
				break ;
			write(1, buff, 1);
			//ft_printf("this is not real\n");
		}
		ft_printf("this is not real\n");
		hijack_stdin(in_file, NULL);
		//char buff[1000];// = "1";
		//while (buff[1])
			//read(in_file, buff, 1000);
		ft_putstr_fd(in_file_name, in_file + 1);
		write(in_file + 1,"\0",1);
		ft_printf("this is not real\n");
		//ft_putstr_fd(in_file_name, 1);
		free(in_file_name);
		close(in_file);
		ft_printf("this is not real\n");
	}
	hijack_stdout(out_file, out_file_name, *append_or_input_flag, list_has_pipes(*lst));
	return (lst);
}
