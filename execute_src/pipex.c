/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:30:18 by ayassin           #+#    #+#             */
/*   Updated: 2022/07/17 18:44:46 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	(*create_pipes(int no_of_pipes))[2]
{
	int	(*fd)[2];
	int	i;

	fd = NULL;
	if (no_of_pipes < 1)
		return (NULL);
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

int	parent_tarp(int count, int (*fd)[2], int no_of_pipes, t_new **lst)
{
	int	errors;

	errors = 0;
	if (no_of_pipes == 0)
		errors = set_pipes(lst, STDIN_FILENO, STDOUT_FILENO);
	else if (count > 0 && count < no_of_pipes)
		errors = set_pipes(lst, fd[count - 1][0], fd[count][1]);
	else if (count == 0)
		errors = set_pipes(lst, STDIN_FILENO, fd[count][1]);
	else
		errors = set_pipes(lst, fd[count - 1][0], STDOUT_FILENO);
	return (errors);
}

int	loopy_parent(t_new *lst, char **path, char **env, int (*fd)[2])
{
	int	count;
	int	id;
	int	status;
	int	no_of_pipes;

	count = 0;
	status = 0;
	no_of_pipes = number_of_pipes(lst);
	while (lst)
	{
		id = fork();
		if (id == 0)
		{
			status = parent_tarp(count, fd, no_of_pipes, &lst);
			close_pipes(fd, no_of_pipes);
			if (status == 0 && lst != NULL
				&& !(lst->flag == 4 && *(lst->token) == '|'))
				status = child_execute (lst, path, env);
			cleanexit(path, fd, status);
		}
		else
			lst = nxt_cmd(lst);
		++count;
	}
	return (status);
}

int	parent_forking5(t_new *lst, char **path, char **env)
{
	int		error;
	int		(*fd)[2];
	int		no_of_pipes;
	int		status;
	int		temp_error;

	temp_error = 0;
	no_of_pipes = number_of_pipes(lst);
	fd = create_pipes(no_of_pipes);
	if (fd == NULL && no_of_pipes != 0)
		return (-1);
	error = loopy_parent(lst, path, env, fd);
	if (error == 0)
	{
		close_pipes(fd, no_of_pipes);
		while (waitpid(-1, &status, 0) > 0)
			if (WEXITSTATUS(status))
				temp_error = WEXITSTATUS(status);
		errno = temp_error;
		ft_printf("The parent is alive %d %d\n", WEXITSTATUS(status), errno);
	}
	free(fd);
	return (error);
}

int	excute(t_new *lst, char **env)
{
	char	**path;
	int		i;

	i = 0;
	if (here_doc_input(lst))
	{
		ft_lstclear(&g_m, free);
		exit(1);
	}
	if (has_parentbuiltins(lst))
	{
		errno = builtins(lst, env);
		return (errno);
	}
	if (!env)
		return (0);
	while (env && env[i] && ft_strncmp_p(env[i], "PATH=", 5) != 0)
		++i;
	if (!env || env[i] == NULL)
		path = NULL;
	else
		path = ft_split(env[i] + 5, ':');
	parent_forking5(lst, path, env);
	clear_str_sep(path);
	return (0);
}
