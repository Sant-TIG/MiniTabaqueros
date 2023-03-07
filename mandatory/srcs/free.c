#include "../incs/minishell.h"

/*
 * Libera un array 2d
 */
void ft_free_2dstr(char **str)
{
	//printf("\nFREE 2DSTR\n");
	int i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}