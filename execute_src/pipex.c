/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:30:18 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/29 16:47:14 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	no_of_pipes = number_of_pipes(lst);
	while (lst)
	{
		id = fork();
		if (id == 0)
		{
			status = parent_tarp(count, fd, no_of_pipes, &lst);
			close_pipes(fd, no_of_pipes);
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
	int		status;
	int		temp_error;

	temp_error = 0;
	no_of_pipes = number_of_pipes(lst);
	fd = create_pipes(no_of_pipes);
	if (fd == NULL)
		return (-1);
	id = loopy_parent(lst, path, env, fd);
	if (id != 0)
	{
		close_pipes(fd, no_of_pipes);
		while (waitpid(-1, &status, 0) > 0)
			if (WEXITSTATUS(status))
				temp_error = WEXITSTATUS(status);
		errno = temp_error;
		ft_printf("The parent is alive %d %d %d\n", WEXITSTATUS(status) , errno , status);
		//ft_printf("The parent is alive %d\n", 0);
	}
	free(fd);
	if (id == 0)
		return (-1);
	return (0);
}

int	builtins(t_new *lst, char **env)
{
	char	*armrest1;
	char	*armrest2;
	int		legrests[2];
	t_new	*temp;
	char	**args;

	armrest1 = NULL;
	armrest2 = NULL;
	legrests[0] = 0;
	legrests[1] = 0;
	temp = lst;
	if (list_has_pipes(temp))
		return (-1);
	redirection_loop(&temp, &armrest1, &armrest2, legrests);
	args = args_array(lst);
	if (args == NULL)
		return (-1);
	return (buitin_switch(lst, args, env));
}

int	has_parentbuiltins(t_new *lst)
{
	if (list_has_pipes(lst))
		return (0);
	else if (lst->token && (ft_strncmp_p(lst->token, "cd", 3) == 0))
		return (1);
	else if (lst->token && (ft_strncmp_p(lst->token, "export", 7) == 0))
		return (1);
	else if (lst->token && (ft_strncmp_p(lst->token, "unset", 6) == 0))
		return (1);
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
	if (has_parentbuiltins(lst))
		return (builtins(lst, env));
	if (!env)
		return (0);
	while (env && env[i] && ft_strncmp_p(env[i], "PATH=", 5) != 0)
		++i;
	if (!env || env[i] == NULL)
		path = NULL;
	else
		path = ft_split(env[i] + 5, ':');
	if (parent_forking5(lst, path, env) == -1)
	{
		clear_str_sep(path);
		ft_lstclear(&g_m, free);
		exit(127);
	}
	clear_str_sep(path);
	return (0);
}