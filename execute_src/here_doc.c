/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:13:47 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/30 19:37:58 by ayassin          ###   ########.fr       */
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

int	here_doc_input(t_new *lst)
{
	char	*delimiter;

	while (lst)
	{
		if (*(lst->token) == '<' && *((lst->token) + 1) == '<') // and flag
		{
			if (*((lst->token) + 2) == '\0')
			{
				lst = lst->next;
				delimiter = lst->token;
				//free(lst->token); // to be added when integrating
				lst->token = line_input(delimiter);
			}
			else
				print_error(lst->token, ": Parsing error in Tokens\n");
		}
		lst = lst->next;
	}
	return (0);
}
