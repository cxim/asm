//
// Created by И Б on 16.05.20.
//

#include "asm.h"

void	free_str(char **s, char ***arr, int i)
{
	int		j;

	if ((i == 1 || i == 2) && *s != 0)
	{
		free(*s);
		*s = 0;
	}
	if ((i == 0 || i == 2) && arr != 0 && *arr != 0)
	{
		j = 0;
		while (arr[0][j])
		{
			free(arr[0][j]);
			arr[0][j] = 0;
			j++;
		}
		free(*arr);
		*arr = 0;
	}
}