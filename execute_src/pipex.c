/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:30:18 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/16 17:25:41 by ayassin          ###   ########.fr       */
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

int	**create_pipes2(int no_of_pipes)
{
	int	**fd;
	int	i;

	if (no_of_pipes < 1)
		return (NULL);
	fd = (int **)malloc(sizeof(*fd) * no_of_pipes);
	if (fd == NULL)
		return (NULL);
	i = 0;
	while (i < no_of_pipes)
	{
		fd[i] = (int *)malloc(sizeof(**fd) * 2);
		if (pipe(fd[i++]) == -1)
		{
			free(fd);
			return (NULL);
		}
	}
	return (fd);
}

int	**free_fds(int no_of_pipes, int **fd)
{
	int	i;

	if (fd == NULL)
		return (0);
	i = 0;
	while (i < no_of_pipes && fd[i])
		free (fd[i++]);
	free (fd);
	fd = NULL;
	return (0);
}

int	(*create_pipes(int no_of_pipes))[2]
{
	int	(*fd)[2];
	int	i;

	// if (no_of_pipes == 0)
	// 	reutrn(NULL);
	fd = malloc(sizeof(*fd) * (no_of_pipes));
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

// int	loopy_parent(t_new *lst, char **path, char **env, int **fd)
int	loopy_parent(t_new *lst, char **path, char **env, int (*fd)[2]) // errors
{
	int	i;
	int	id;
	int	status;
	// int	prev_id;
	int	no_of_pipes;

	i = 0;
	status = 0;
	// prev_id = 0;
	no_of_pipes = number_of_pipes(lst);
	//close(fd[0][0]);
	ft_printf("no of pipes is %d\n", no_of_pipes);
	while (lst)
	{
		id = fork();
		if (id == 0)
		{
			// child_manger(lst, fd, i);
			// if (prev_id != 0)
			// {
			// 	//sleep(1);
			// 	waitpid(prev_id, &status, 0);
			// 	//ft_printf("the previous kids status %d\n", WEXITSTATUS(status));
			// }
			if (no_of_pipes == 0)
				status = set_pipes(&lst, STDIN_FILENO, STDOUT_FILENO);
			else if (i > 0 && i < no_of_pipes)
			{
				ft_printf("GREETINGS %d\n", i);
				status = set_pipes(&lst, fd[i - 1][0], fd[i][1]);
			}
			else if (i == 0)
				status = set_pipes(&lst, STDIN_FILENO, fd[i][1]);
			else
				status = set_pipes(&lst, fd[i - 1][0], STDOUT_FILENO);
			close_pipes(fd, no_of_pipes);
			if (status == 0)
				child_execute (lst, path, env);
			break ;
		}
		else
		{
			//close_some_pipes(fd, i);
			lst = nxt_cmd(lst);
			// (void)fd;
			// prev_id = id;
		}
		++i;
	}
	return (id);
}

int	loopy_parent2(t_new *lst, char **path, char **env, int (*fd)[2]) // errors
{
	int	i;
	int	id;
	int	status;
	// int	prev_id;
	int	no_of_pipes;

	i = 0;
	status = 0;
	// prev_id = 0;
	no_of_pipes = 2;
	ft_printf("no of pipes is %d\n", no_of_pipes);
	while (lst)
	{
		id = fork();
		if (id == 0)
		{
			// if (prev_id != 0)
			// {
			// 	waitpid(prev_id, &status, 0);
			// }
			ft_printf("gsadgasjdja\n");
			if (i == 0)
			{
				dup2(fd[0][1], STDOUT_FILENO); 
			}
			else if (i == 1)
			{
				dup2(fd[1][1], STDOUT_FILENO);
				dup2(fd[0][0], STDIN_FILENO);
			}
			else if (i == 2)
				dup2(fd[1][0], STDIN_FILENO);
			// close(fd[0][0]);
			// close(fd[0][1]);
			// close(fd[1][0]);
			// close(fd[1][1]);
			if (status == 0)
				child_execute (lst, path, env);
			break ;
		}
		else
		{
			lst = nxt_cmd(lst);
			// prev_id = id;
		}
		++i;
	}
	return (id);
}

int	parent_forking5(t_new *lst, char **path, char **env)
{
	int		id;
	int		status;
	int		(*fd)[2];
	//int		**fd;
	int		no_of_pipes;

	status = 0;
	no_of_pipes = number_of_pipes(lst);
	fd = create_pipes(no_of_pipes);
	if (fd == NULL)
		return (-1);
	id = loopy_parent(lst, path, env, fd);
	if (id != 0)
	{
		close_pipes(fd, no_of_pipes);
		//waitpid(id, &status, 0);
		while(wait(NULL) > 0)
		;
		if (WEXITSTATUS(status))
			ft_printf("THE CHILD HAD A PROBLEM\n");
		ft_printf("The parent is alive %d\n", WEXITSTATUS(status));
	}
	free(fd);
	// free_fds(no_of_pipes, fd);
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

// t_new	**set_pipes(t_new **lst, int in_file, int out_file)
// {
// 	char	*in_file_name;
// 	char	*out_file_name;
// 	int		append_flag;
// 	int		skip_flag;
// 	t_new	*temp;

// 	in_file_name = NULL;
// 	out_file_name = NULL;
// 	append_flag = 0;
// 	skip_flag = 0;
// 	temp = *lst;
// 	if (*(temp->token) == '|') // use flag
// 		ft_printf("DUCK");
// 	while (temp && *(temp->token) != '|') //use flag
// 	{
// 		// redirection
// 		if (temp && *(temp->token) == '<') // and flag
// 			in_file_name = redirect_input(&temp, &skip_flag);
// 		if (temp && *(temp->token) == '>') // and flag
// 			out_file_name = redirect_output(&temp, &skip_flag, &append_flag);
// 		if (skip_flag == 1)
// 			skip_flag = 0;
// 		else
// 			temp = temp->next;
// 	}
// 	if(temp != NULL)
// 		temp->next = NULL; // remeber to free the list for the child
// 	while (*lst && ft_strchr("<>", *((*lst)->token))) // check flags (and free)
// 		*lst = (*lst)->next;
// 	temp = *lst;
// 	// Redirection
// 	append_flag = (O_APPEND * (append_flag)) | (O_TRUNC * (!append_flag));
// 	if (in_file_name != NULL)
// 		in_file = open(in_file_name, O_RDONLY);
// 	if (out_file_name != NULL)
// 		out_file = open(out_file_name, O_WRONLY | O_CREAT | append_flag);
// 	dup2(in_file, STDIN_FILENO);
// 	if (list_has_pipes(*lst) || out_file_name != NULL) // or redirection
// 	{	
// 		dup2(out_file, STDOUT_FILENO);
// 	}
// 	return (lst);
// }

// int	parent_forking(t_new *lst, char **path, char **env) // works for miltiple pipes eith a single wc
// {
// 	int		id;
// 	int		status;
// 	int		fd[2];

// 	id = 1;
// 	status = 0;
// 	if (pipe(fd) == -1)
// 		return (-1);
// 	while (lst)
// 	{
// 		id = fork();
// 		if (id == 0)
// 		{
// 			ft_printf("I am a child pid = %d with parent %d\n", getpid(), getppid());
// 			dup2(fd[0], STDIN_FILENO);
// 			if (list_has_pipes(lst))
// 			{
// 	 			printf("SWITCHING stdout\n");
// 				// lst_print(lst);
// 				// dup2(fd[0], STDIN_FILENO);
// 				dup2(fd[1], STDOUT_FILENO);
// 			}
// 			close(fd[0]);
// 			close(fd[1]);
// 			child1 (lst, path, env);
// 			exit(-1);
// 		}
// 		else
// 		{
// 			//Hello I was restored2\n
// 			//close(fd[0]);
// 			//close(fd[1]);
// 			ft_printf("A Parent is alive pid = %d with child= %d\n", getpid(), id);
// 			while (lst && *(lst->token) != '|') //use flag
// 				lst = lst->next;
// 			if (lst && *(lst->token) == '|') //use flag
// 				lst = lst->next;
// 			(void)status;
// 			//close(fd[0]);
// 			//close(fd[1]);
// 			//waitpid(id, &status, 0);
// 			//pipe(fd);
// 			//close(fd[0]);
// 			//wait(&status);
// 		}
// 	}
// 	if (id != 0)
// 	{
// 		//wait(&status);
// 		close(fd[0]);
// 		close(fd[1]);
// 		waitpid(id, &status, 0);
// 		ft_printf("The parent is alive\n");
// 	}
// 	return (0);
// }