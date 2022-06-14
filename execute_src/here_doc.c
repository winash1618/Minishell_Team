/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 08:13:47 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/14 19:10:50 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			if (ft_strjoin_minishell(&line, one_line) < 0
				|| ft_strjoin_minishell(&line, "\n"))
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
			{
				delimiter = ((lst->token) + 2);
				// //free(lst->token); // to be added for when inegrating
				lst->token = ft_strdup("<<");
				ft_strjoin_minishell(&(lst->token), line_input(delimiter));
			}
		}
		lst = lst->next;
	}
	return (0);
}
