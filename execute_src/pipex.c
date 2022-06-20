/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:30:18 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/20 09:31:17 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_new	*nxt_cmd(t_new *lst)
{
	while (lst && *(lst->token) != '|') //use flag
		lst = lst->next;
	if (lst && *(lst->token) == '|') //use flag
		lst = lst->next;
	return (lst);
}

int	(*create_pipes(int no_of_pipes))[2]
{
	int	(*fd)[2];
	int	i;

	fd = malloc(sizeof(*fd) * (no_of_pipes));
	if (fd == NULL)
		return (NULL);
	if (fd == NULL)
		return (NULL);
	i = 0;
	while (i < no_of_pipes)
	{
		if (pipe(fd[i++]) == -1)
		{
			free(fd);
			return (NULL);
		}
	}
	return (fd);
}

int	loopy_parent(t_new *lst, char **path, char **env, int (*fd)[2])
{
	int	count;
	int	id;
	int	status;
	int	no_of_pipes;

	count = 0;
	no_of_pipes = number_of_pipes(lst);
	while (lst)
	{
		id = fork();
		if (id == 0)
		{
			if (no_of_pipes == 0)
				status = set_pipes(&lst, STDIN_FILENO, STDOUT_FILENO);
			else if (count > 0 && count < no_of_pipes)
				status = set_pipes(&lst, fd[count - 1][0], fd[count][1]);
			else if (count == 0)
				status = set_pipes(&lst, STDIN_FILENO, fd[count][1]);
			else
				status = set_pipes(&lst, fd[count - 1][0], STDOUT_FILENO);
			close_pipes(fd, no_of_pipes);
			ft_putstr_fd("*******\n", 2);
			ft_putstr_fd(lst->token, 2);
			ft_putstr_fd("\n*******\n", 2);
			if (status == 0)
				child_execute (lst, path, env);
			break ;
		}
		else
			lst = nxt_cmd(lst);
		++count;
	}
	return (id);
}

int	parent_forking5(t_new *lst, char **path, char **env)
{
	int		id;
	int		(*fd)[2];
	int		no_of_pipes;

	no_of_pipes = number_of_pipes(lst);
	fd = create_pipes(no_of_pipes);
	if (fd == NULL)
		return (-1);
	id = loopy_parent(lst, path, env, fd);
	if (id != 0)
	{
		close_pipes(fd, no_of_pipes);
		while (wait(NULL) > 0)
			;
		ft_printf("The parent is alive %d\n", 0);
	}
	free(fd);
	if (id == 0)
		return (-1);
	return (0);
}

int	excute(t_new *lst, char **env)
{
	char	**path;
	int		i;

	i = 0;
	(void)lst;
	if (here_doc_input(lst))
		exit(-1); //change code based on error
	if (!env)
		return (0);
	while (env[i] && ft_strncmp_protected(env[i], "PATH=", 5) != 0)
		++i;
	if (env[i] == NULL)
		return (0);
	//env[i] = ft_strnstr(env[i], "PATH=", 5);
	// split path
	path = ft_split(env[i] + 5, ':');
	if (path == NULL)
		return (-1);
	if (parent_forking5(lst, path, env) == -1)
	{
		clear_str_sep(path);
		// clear list
		exit(50);
	}
	clear_str_sep(path);
	return (0);
}