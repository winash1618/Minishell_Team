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


// #include "minishell.h"
// t_list *g_m;

// int main (int ac, char **av, char **env)
// {
// 	char *str = "\"\'\"$PATH\"\'\"";
// 	// t_list *lst = get_expanded_string2(str, env);

// 	printf("%d \n", errno);
// 	return (0);
// }

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
  
int main ()
{
    FILE * fp;
    fp = fopen ("filedoesnotexist.txt", "rb");
  
    if (fp == NULL)
    {
        printf("Value of errno: %d\n", errno);
        printf("Error opening the file: %s\n",
                             strerror(errno));
        perror("Error printed by perror");
  
        exit(EXIT_FAILURE);
        printf("I will not be printed\n");
    }
  
    else
    {
        fclose (fp);
        exit(EXIT_SUCCESS);
        printf("I will not be printed\n");
    }
    return 0;
}