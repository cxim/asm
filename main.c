//
// Created by И Б on 16.05.20.
//

#include "asm.h"

//тест для статик переменной
//void	get_data(t_data *data)
//{
//	data->line = 0;
//	data->comment = NULL;
//	data->name = NULL;
//	data->fd_r = 0;
//	data->fd_w = 0;
//	data->total = 0;
//}



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
	//get_data(data);
	data->fd_r = open(argv[argc - 1], O_RDONLY);
	if (data->fd_r < 3 || read(data->fd_r, data->name, 0) < 0)
		exit(ft_printf("Error: file %s could't be read\n", argv[argc - 1]) != 0); //исправить на 2 поток вывод
	conversion(data);


	exit(123);
	return (0);
}