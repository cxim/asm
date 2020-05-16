//
// Created by И Б on 16.05.20.
//

#include "asm.h"

//тест для статик переменной
//t_data	*get_data(t_data *data)
//{
//	static t_data	*saved_d = 0;
//
//	if (!saved_d)
//		saved_d = data;
//	return (saved_d);
//}



void	conversion(t_data *data)
{
	char 	*s;

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
	data = (t_data *)malloc(sizeof(t_data));
	//get_data(data);
	data->fd_r = open(argv[argc - 1], O_RDONLY);
	if (data->fd_r < 3 || read(data->fd_r, data->name, 0) < 0)
		exit(ft_printf("Error: file %s could't be read\n", argv[argc - 1]) != 0); //исправить на 2 поток вывод
	conversion(data);

	return (0);
}