//
// Created by И Б on 16.05.20.
//

#include "asm.h"


t_data	*get_data(t_data *data)
{
	static t_data *s_data = 0;

	if (!s_data)
		s_data = data;
	return (s_data);
}



void	conversion(t_data *data)
{
	char 	*s;

	//data->line = 0; //?
	while (get_clean_str(data, &s) > 0)
	{
		data->line++;
		if (ft_strlen(s) > 0)
			choose_do(data, s); // парсинг коментов+инструкций+меток и тд
		free_str(&s, NULL, 1);
	}
	free_str(&s, NULL, 1);
}

int		main(int argc, char** argv)
{
	char 	*f_name;
	t_data	*data;

	if (argc > 2)
		exit(ft_printf("usage: ./asm file_name\n") != 0);
	data = (t_data *)ft_memalloc(sizeof(t_data));
	get_data(data);
	data->fd_r = open(argv[argc - 1], O_RDONLY);
	if (data->fd_r < 3 || read(data->fd_r, data->name, 0) < 0)
		exit(ft_printf("Error: file %s could't be read\n", argv[argc - 1]) != 0); //исправить на 2 поток вывод
	conversion(data);

//	t_label *tmp = data->label;
	t_oper *tm = data->op;
	int i;
	while (tm)
	{
		i = -1;
		while (++i < 3)
			printf("%d %d %d %d", tm->argum_size[i], tm->argum[i], tm->argum_type[i], tm->argum_is_label[i]);
		printf("\n");
		tm = tm->next;
	}
//	while (tmp)
//	{
//		//printf("%s\n", tmp->name, );
//		tmp = tmp->next;
//	}
	check_all(data);

	exit(123);
	return (0);
}