/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 09:16:46 by ayassin           #+#    #+#             */
/*   Updated: 2022/05/27 15:47:40 by mkaruvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
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
	char *key;
	char *value;
	struct var *next;
	struct var *prev;
}	t_var;

// for saving commands
typedef struct list
{
	char	*token;
	int	flag;
	char *es; // expanded string.
	int d_flag; // indicate presence of dollar sign in the string.
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
} t_info;


int	excute(t_new *lst, char **env);



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
char *go_past_quotes(char *s, char ch);
// ----------handling normal-------------------
int get_word_len(char *line); //find the word length for normal part in a string
char *normal_word(char *line);
void normal_lexer (t_new **pars, t_info *info, char *str);//normal part
char *get_word(t_info *info, char *line);
int check_word_for_parsing(char *line);
// ---------List operations for words--------------------
void lst_add_new(t_new **pars, char *str, t_info *info);
void lst_add_back(t_new **pars, char *str, t_info *info);
void lst_print(t_new *pars);
//----------List operations for variable assignment-----
void lst_add_newvar(t_var **var, char *line);
void lst_add_backvar(t_var **var, char *line);
void lst_print_vars(t_var *vars);
//----------variable assignment-------------------------
int check_var(char *line, t_info *info);
int get_vars(char *line);
int get_len(char *line);
char *get_key(char *line);
char *get_value(char *line);
void var_lexer (t_var **var, char *line);
// ----------------Handling dollar----------------------
void find_dollar_presence(t_new *cmd);// Find the presence of dollar
int is_meta(char c);// check if the character meta or not returns one if true.
int get_strlen(char *str);// get string length for dollar expansion
int	ft_strjoin_ps(char **prestr, char *sufstr, int8_t freesuf);//string join mehdy version
char *get_dollar_path(char *str, char **env);//  if success returns the matching env variable part after the equal sign.
char *get_str(char *str);// It returns normal string until dollar sign.
char *get_expanded_string(char *str, char **env);// It returns entire string with expansion
//---------------------------------------------//
//--------------Parsing Functions--------------//
//---------------------------------------------//


#endif