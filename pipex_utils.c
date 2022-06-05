/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 14:13:31 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/05 16:34:22 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* free the output of ft_split after we are done with it*/
void	clear_str_sep(char **str_sep)
{
	int	i;

	i = 0;
	if (str_sep)
	{
		while (str_sep[i])
			free(str_sep[i++]);
		free (str_sep);
	}
}

/*Appends suffex string "sufstr" to the prefix string "prestr" 
up until "sufstr" char 0 or new line. 
Return 1 if sufstr has new lone, -1 if Memory allocation failed, 0 otherwise
**malloc DANGER**/
int	ft_strjoin_minishell(char **prestr, char *sufstr)
{
	int		i1;
	int		i2;
	int		lineflag;
	char	*fullstr;

	i1 = 0;
	i2 = 0;
	lineflag = 0;
	fullstr = (char *)malloc(ft_strlen(*prestr) + ft_strlen(sufstr) + 1);
	if (fullstr == NULL)
		return (-10);
	while (*prestr && (*prestr)[i1])
	{
		fullstr[i1] = (*prestr)[i1];
		++i1;
	}
	while (sufstr[i2] && sufstr[i2] != '\n')
		fullstr[i1++] = sufstr[i2++];
	fullstr[i1] = 0;
	if (*prestr)
		free (*prestr);
	*prestr = fullstr;
	return (lineflag);
}

int	number_of_pipes(t_new *lst)
{
	int	count;

	count = 0;
	if (lst == NULL)
		return (0);
	while (lst)
	{
		if (*(lst->token) == '|') // use flag
			++count;
		lst = lst->next;
	}
	return (count);
}

int	list_has_pipes(t_new *lst)
{
	if (lst == NULL)
		return (0);
	while (lst)
	{
		if (*(lst->token) == '|') // use flag
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	close_pipes(int (*fd)[2], int no_of_pipes)
{
	int	i;

	i = 0;
	while (i < no_of_pipes)
	{
		close (fd[i][0]);
		close (fd[i][1]);
		++i;
	}
}