/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:30:18 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/04 16:15:00 by ayassin          ###   ########.fr       */
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

int	child1(t_new *lst, char **path, char **env)
{
	int		i;
	char	*limits;
	int		arg_count;
	t_new	*temp;
	char	**args;

	limits = "<>|"; // use flags
	arg_count = 0;
	temp = lst;
	while (temp && !ft_strchr(limits, *(temp->token))) // check flags (and free)
	{
		++arg_count;
		temp = temp->next;
	}
	args = (char **)malloc(sizeof(*args) * (arg_count + 1));
	i = 0;
	temp = lst;
	while (i < arg_count)
	{
		args[i++] = temp->token;
		temp = temp->next;
	}
	args[i] = NULL;
	i = 0;
	while (path[i])
	{
		ft_strjoin_minishell(&(path[i]), "/");
		ft_strjoin_minishell(&(path[i]), lst->token);
		execve(path[i], args, env);
		++i;
	}
	free(args);
	free(env);
	return (1);
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

t_new	**set_pipes(t_new **lst, int in_file, int out_file)
{
	char	*in_file_name;
	char	*out_file_name;
	int		append_flag;
	int		skip_flag;
	t_new	*temp;

	in_file_name = NULL;
	out_file_name = NULL;
	append_flag = 0;
	skip_flag = 0;
	temp = *lst;
	if (*(temp->token) == '|') // use flag
		ft_printf("DUCK");
	// ft_printf("_____________GREEN_________\n");
	// lst_print(*lst);
	while (temp && *(temp->token) != '|') //use flag
	{
		// input redirection
		if (temp && *(temp->token) == '<' && *((temp->token) + 1) != '<') // use flag
		{
			if (*((temp->token) + 1) != '\0')
				in_file_name = (temp->token) + 1;
			else if (temp->next)
			{
				in_file_name = temp->next->token;
				skip_node(&temp, &skip_flag);
			}
			else
				ft_printf("parse error near \n");
			// ft_printf("The file is %s\n", in_file_name);
			skip_node(&temp, &skip_flag);
		}
		// output redirection
		if (temp && *(temp->token) == '>') // use flag
		{
			if (*((temp->token) + 1) == '>') // use flag
				append_flag = 1;
			else
			{
				append_flag = 0;
				//empty_file(); // remove a file
			}
			if (*((temp->token) + 1 + append_flag) != '\0')
				out_file_name = (temp->token) + 1 + append_flag;
			else if (temp->next)
			{
				out_file_name = temp->next->token;
				skip_node(&temp, &skip_flag);
			}
			else
				ft_printf("parse error near \n");
			skip_node(&temp, &skip_flag);
		}
		if (skip_flag == 1)
			skip_flag = 0;
		else
			temp = temp->next;
	}
	if(temp != NULL)
		temp->next = NULL; // remeber to free the list for the child
	while (*lst && ft_strchr("<>", *((*lst)->token))) // check flags (and free)
	{
		*lst = (*lst)->next;
	}
	temp = *lst;
	// ft_printf("_____________PURPLE_________\n");
	// lst_print(*lst);
	// Redirection
	append_flag = (O_APPEND * (append_flag)) | (O_TRUNC * (!append_flag));
	if (in_file_name != NULL)
		in_file = open(in_file_name, O_RDONLY);
	if (out_file_name != NULL)
		out_file = open(out_file_name, O_WRONLY | O_CREAT | append_flag);
	dup2(in_file, STDIN_FILENO);
	if (list_has_pipes(*lst) || out_file_name != NULL) // or redirection
	{	
		dup2(out_file, STDOUT_FILENO);
	}
	(void)in_file;
	(void)out_file;
	return (lst);
}

int	parent_forking5(t_new *lst, char **path, char **env)
{
	int		id;
	int		status;
	int		i;
	int		(*fd)[2];
	int		no_of_pipes;

	id = 1;
	status = 0;
	no_of_pipes = number_of_pipes(lst);
	fd = malloc(sizeof(*fd) * (no_of_pipes));
	i = 0;
	while (i < no_of_pipes)
	{
		if (pipe(fd[i]) == -1)
			return (-1);
		++i;
	}
	i = 0;
	while (lst)
	{
		id = fork();
		if (id == 0)
		{
			// ft_printf("_____________GREEN %d/%d_________\n", i, no_of_pipes);
			// lst_print(lst);
			if (i > 0)
				set_pipes(&lst, fd[i - 1][0], fd[i][1]);
			else
				set_pipes(&lst, STDIN_FILENO, fd[i][1]);
			// if (i > 0)
			// 	dup2(fd[i - 1][0], STDIN_FILENO);
			// if (list_has_pipes(lst))
			// {	
			// 	dup2(fd[i][1], STDOUT_FILENO);
			// }
			for(int j = 0; j < no_of_pipes; ++j)
			{
				close (fd[j][0]);
				close (fd[j][1]);
			}
			// ft_printf("_____________GREEN %d/%d_________\n", i, no_of_pipes);
			// lst_print(lst);
			child1 (lst, path, env);
			exit(-1); // temp sol
		}
		else
		{
			while (lst && *(lst->token) != '|') //use flag
				lst = lst->next;
			if (lst && *(lst->token) == '|') //use flag
				lst = lst->next;
			(void)status;
		}
		++i;
	}
	if (id != 0)
	{
		for(int j = 0; j < no_of_pipes; ++j)
		{
			close (fd[j][0]);
			close (fd[j][1]);
		}
		waitpid(id, &status, 0);
		ft_printf("The parent is alive\n");
	}
	free(fd);
	return (0);
}

int	excute(t_new *lst, char **env)
{
	char	**path;
	int		i;

	i = 0;
	(void)lst;
	//Find Path
	while (env[i] && !ft_strnstr(env[i], "PATH=", 5))
		++i;
	env[i] = ft_strnstr(env[i], "PATH=", 5);
	//Check if path is ther
	if (env[i] == NULL)
		return (0);
	// split path
	//ft_printf("%s\n", env[i]);
	path = ft_split(env[i] + 5, ':');
	parent_forking5(lst, path, env);
	clear_str_sep(path);
	return (0);
}

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