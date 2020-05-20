//
// Created by student on 20.0

#include "asm.h"

void	split_argums(char **ret, char ***tmp, int argc, int line_nb)
{
	int		i[MAX_ARG];

	i[0] = 0;
	i[2] = 0;
	while (tmp[i[0]] != NULL && i[0] < argc)
	{
		i[1] = 0;
		while (tmp[i[0]][i[1]] && i[2] <= MAX_ARG)
		{
			if (ft_strlen(tmp[i[0]][i[1]]) > 0)
			{
				ret[i[2]] = ft_strdup(tmp[i[0]][i[1]]);
				i[2]++;
			}
			i[1]++;
		}
		free_str(NULL, &tmp[i[0]], 0);
		i[0]++;
	}
	if (i[2] > MAX_ARG)
		exit(ft_printf("ERROR: excess args (> MAX_ARGS) at line %d\n", line_nb));
	ret[i[2]] = 0;
}

char	**cleaning_str(int argc, char **argv, int line_nb)
{
	char 	**ret;
	char 	***tmp;
	int		i;

	if (MAX_ARG < 1)
		exit(ft_printf("ERROR: MAX_ARG value is not valid\n"));
	ret = (char**)ft_memalloc(sizeof(char*)  * (MAX_ARG + 1));
	tmp = (char***)ft_memalloc(sizeof(char**) * (argc + 1));
	while (i < argc)
	{
		tmp[i] = ft_split(argv[i], ',');
		i++;
	}
	split_argums(ret, tmp, argc, line_nb);
	free(tmp);
	return (ret);
}

int 	get_argums(t_oper *op, char **argv, int argc, t_data *data)
{
	char 	**clean_str;
	int 	i;
	int		args_qty_size;
	int		allowed_types;

	clean_str = cleaning_str(argc, argv, data->line);
	int j = 0;
	while (clean_str[j])
	{
		printf("%s", clean_str[j]);
		j++;
	}
	return 0;
}