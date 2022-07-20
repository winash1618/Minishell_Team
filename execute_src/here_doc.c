/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:13:47 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/20 19:43:01 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*line_input(char *delimiter)
{
	char	*line;
	char	*one_line;

	line = NULL;
	one_line = NULL;
	while (1)
	{
		one_line = readline("> ");
		if (ft_strncmp_p(one_line, delimiter, ft_strlen(delimiter) + 1) != 0)
		{
			if (ft_strjoin_ms(&line, one_line) < 0 || ft_strjoin_ms(&line, "\n"))
			{
				free(one_line);
				free(line);
				return (NULL);
			}
			free(one_line);
		}
		else
			break ;
	}
	free(one_line);
	if (line == NULL)
		line = ft_strdup("");
	return (line);
}

char	*line_input_parent(char *delimiter)
{
	int		fd[2];
	char	*line;
	int		len;

	pipe(fd);
	if (fork() == 0)
	{
		close(fd[0]);
		line = line_input(delimiter);
		len = ft_strlen(line);
		write(fd[1], &len, sizeof(int));
		ft_putstr_fd(line, fd[1]);
		close(fd[1]);
		if (line)
			free(line);
		exit(0);
	}
	close(fd[1]);
	read(fd[0], &len, sizeof(int));
	line = malloc(sizeof(char) * (len + 1));
	read(fd[0], line, len);
	close(fd[0]);
	line[len] = 0;
	return (line);
}

int	here_doc_input(t_new *lst)
{
	char	*delimiter;

	while (lst)
	{
		if (*(lst->token) == '<'
			&& *((lst->token) + 1) == '<' && lst->flag == 4)
		{
			if (*((lst->token) + 2) == '\0')
			{
				lst = lst->next;
				delimiter = lst->token;
				lst->token = line_input(delimiter); //check what is happining
				if (ft_lstadd_backhelper(&g_m, lst->token))
				{
					free(lst->token);
					return (1);
				}
			}
			else
				print_error(lst->token, ": Parsing error in Tokens\n", 22);
		}
		lst = lst->next;
	}
	return (0);
}
