#include <stdio.h>
#include <string.h>

int is_quote(char c)
{
	if (c == '"' || c == 39)
		return (1);
	return (0);
} 

int main()
{
	int c;
	int d;

	d = 0;
	c = 0;
	char *temp = "\'sfs\'df\'\"\'\"\'\'\""; 
	char *temp2 = strdup(temp);

	int i = 0;
	while (temp2[i])
	{
		if (temp2[i] == '"')
		{
			i++;
			while (temp2[i] != '"' && temp2[i]) 
			{
				temp2[i] = 'a';
				i++;
			}
			if (temp2[i])
				i++;
		}
		else if (temp2[i] == 39)
		{
			i++;
			while (temp2[i] != 39 && temp2[i]) 
			{
				temp2[i] = 'a';
				i++;
			}
			if (temp2[i])
				i++;
		}
		else
			i++;
	}
	i = 0;
	while (temp2[i])
	{
		if (temp2[i] == '"')
			c++;
		else if (temp2[i] == 39)
			d++;
		i++;
	}
	if (c % 2 || d % 2)
		printf("quote not complete");
}
