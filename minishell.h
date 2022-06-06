/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassin <ayassin@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:16:46 by ayassin           #+#    #+#             */
/*   Updated: 2022/06/06 14:12:48 by ayassin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <errno.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>
# include <stdlib.h>
# include <termcap.h> 
# include <readline/readline.h>
# include <string.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

// for saving local variable
typedef struct var 
{
	char *key; // consider "x = y" then x is key
	char *value; // y is value
	int err_flag;
	struct var *next;
	struct var *prev;
}	t_var;

// for saving commands
typedef struct list
{
	char	*token; // contains splited string 
	int	flag; // returns 1 if double quote is present, returns 2 if single quote, 3 if normal word.
	t_list *lst;// used for expansion of word without quote
	char *es; // expanded string.
	int d_flag; // indicate presence of dollar sign in the string.
	int l_flag; // true if < is present and l2_flag is false
	int l2_flag; // true if << is present 
	int r_flag; // true if > is present and r2_flag is false
	int r2_flag; // true if >> is present 
	int p_flag; // indicate presence of pipe in a token
	int err_flag;// true an error is present
	struct list	*next;
	struct list	*prev;
}	t_new;

// for saving required information
typedef struct info
{
	int flag;
	int w_flag; // if the string is double quoted then this flag exist.
	int e_flag; // if the string starts with an equal sign it's an error;
	int q_flag; // exist when count either of the quotes is odd
	int dq_flag; // presence of $ then " or '
	int err_flag;
} t_info;

// Global variable declaration
extern t_list *g_m;
//---------------------------------------------//
//--------------Parsing Functions--------------//
//---------------------------------------------//
int ft_isspace(char c);// return 1 if space tab or newline 
int is_quote(char c); // return 0 if double or single quote is found.
void ft_clearscreen(void);// Used to clear the screen
char *ft_readline(void);// Display a prompt and wait for input 
// --------handling quote----------------------
int ft_strlen_ch(char *line, char c);// find length of word until quote.
void quote_counter(char *line, t_info *info);//count the number single and double quotes saperately if there is odd number return false
char *quoted_word(char *line, char ch);//get the quoted word without quotes
char *go_past_quotes(char *s, char ch); // move pointer after the closing quote
// ----------handling normal-------------------
int get_word_len(char *line); //find the word length for normal part in a string
char *normal_word(char *line); //get the normal word
void normal_lexer (t_new **pars, t_info *info, char *str);//normal part
char *get_word(t_info *info, char *line); 
int check_word_for_parsing(char *line);
// ---------List operations for words--------------------
void lst_add_new(t_new **pars, char *str, t_info *info); // adds new node to the pars structure
void lst_add_back(t_new **pars, char *str, t_info *info); // adds new node at back side of pars structure
void lst_print(t_new *pars); //prints contents of structure var
void lst_rev_print(t_new *pars);
//----------List operations for variable assignment-----
void lst_add_newvar(t_var **var, char *line); // adds new node to the var structure
void lst_add_backvar(t_var **var, char *line); // adds new node at back side of var structure
void lst_print_vars(t_var *vars); // print structure var
//----------variable assignment-------------------------
int check_var(char *line, t_info *info);
int get_vars(char *line);
int get_len(char *line);
char *get_key(char *line);
char *get_value(char *line);
void var_lexer (t_var **var, char *line);
////////////////////////////////////////////
void lst_add_front(t_new **cmd, t_list *lst);
void lst_big_new(t_new **cmd, t_list *lst);
void lst_add(t_new **cmd, t_list *lst);
void lst_skip_node(t_new **cmd);
void make_big_list(t_new **cmd);
////////////////////////////////////////////
// ----------------Handling dollar----------------------
void make_all_zero(t_new *cmd);// utility for find redirection presence
void find_redirection_presence(t_new *cmd); //handle the flags for redirection >>, >, <<, <
void find_dollar_presence(t_new *cmd);// Find the presence of dollar
int is_meta(char c);// check if the character meta or not returns one if true.
int is_no_dollar_meta(char c);// contains |, <, >
int is_no_dollar_meta1(char c);// space, tab, new line, &, ;, ()
int is_meta_special(char c);// contatins space, tab, new line, |&;()<>:?+-=!@#$^{}[]|%*,.~
int get_strlen(char *str);// get string length for dollar expansion
int	ft_strjoin_ps(char **prestr, char *sufstr, int8_t freesuf);//string join mehdy version
char *get_dollar_path(char *str, char **env);//  if success returns the matching env variable part after the equal sign.
char *get_str(char *str);// It returns normal string until dollar sign.
char *get_expanded_string(char *str, char **env);// It returns entire string with expansion
void dollar_expansion(t_new *cmd, char **env);//loop through cmd and do dollar expansion.
t_list *get_expanded_list(char *str, char **env);//It returns a list of expanded string
//---------------------------------------------//
//--------------Parsing Functions--------------//
//---------------------------------------------//
int		excute(t_new *lst, char **env);

//pipex_utils.c
int		ft_strjoin_minishell(char **prestr, char *sufstr);
void	clear_str_sep(char **str_sep);
void	close_pipes(int (*fd)[2], int no_of_pipes);
int		number_of_pipes(t_new *lst);
int		list_has_pipes(t_new *lst);
int		ft_strncmp_protected(const char *s1, const char *s2, size_t n); // in redirction for the moment

//child.c
char	**args_array(t_new *lst);
int		child_execute(t_new *lst, char **path, char **env);

//redirection.c
void	skip_node(t_new **lst, int *skip_flag);
char	*redirect_input(t_new **lst, int *skip_flag);
int		empty_file(char *file_name);
char	*redirect_output(t_new **lst, int *skip_flag , int *append_flag);
char	*line_input(char *delimiter);

//redirection2.c
int		hijack_stdin(int in_file, char *in_file_name); //handel errors
int		hijack_stdout(int out_file, char *out_file_name, int append_flag, int flag); //handle errors
int		redirection_loop(t_new **lst, char **in_file_name, char **out_file_name, int *append_flag);
t_new	**set_pipes(t_new **lst, int in_file, int out_file);


//temp_list.c
t_new	*temp_lst_newnode(char *str);
void	temp_list_clear(t_new **lst);
void	print_strarr(char **args);
void	temp_lstadd_back(t_new **lst, t_new *node);
#endif