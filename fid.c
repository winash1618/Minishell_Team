// #include <errno.h>

// #include <stdio.h>

// #include <stdlib.h>

// int main(void)

// {

//    FILE *fp;

//    errno = 0;

//    fp = fopen("Nofile", "r");

//    if ( errno != 0 ) 

//    {

//      perror("Error occurred while opening file.\n");

//      exit(1);

//    }
// 	return (1);
// }3


#include "minishell.h"
t_list *g_m;

int main (int ac, char **av, char **env)
{
	char *str = "\"\'\"$PATH\"\'\"";
	t_list *lst = get_expanded_string2(str, env);
	
	return (0);
}
