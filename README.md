# Minishell_Team

## Assumption
- If the command starting with quote and contains space before ending quote then its an error. like "ls " or "ls -la", etc.
- "ls"-la is an error
- echo $PWD?$PWD:$PWD - will take all the three PWD.

## Resources
- https://www.ibm.com/docs/en/rdfi/9.6.0?topic=errors-checking-errno-value
- https://github.com/simon-ameye/42-minishell_bash_tester_2022
- https://www.ibm.com/docs/en/rdfi/9.6.0?topic=errors-checking-errno-value
- https://medium.com/swlh/understanding-pipes-in-unix-with-a-sample-implementation-9fe110d36412


## for help
- gcc -g get_expanded_string_test.c libft/libft.a ft_printf/libftprintf.a parsing/parsing.a

## For reference
	- l2_flag 	int
	- r_flag  	int
	- r2_flag 	int
	- p_flag  	int
	- err_flag	int
	- next    	t_new
	- prev    	t_new
	- token   	char *
	- flag    	int
	- lst     	t_list *
	- es      	char *
	- d_flag  	int
	- l_flag  	int
