//
// Created by И Б on 17.05.20.
//

#include "asm.h"

int 	is_inst_2(char *str)
{
	if (ft_strcmp(str, "fork\0") == 0)
		return (12);
	else if (ft_strcmp(str, "lld\0") == 0)
		return (13);
	else if (ft_strcmp(str, "lldi\0") == 0)
		return (14);
	else if (ft_strcmp(str, "lfork\0") == 0)
		return (15);
	else if (ft_strcmp(str, "aff\0") == 0)
		return (16);
	else
		return (0);
}

int 	is_instrctn(char *str)
{
	if (ft_strcmp(str, "live\0") == 0)
		return (1);
	else if (ft_strcmp(str, "ld\0") == 0)
		return (2);
	else if (ft_strcmp(str, "st\0") == 0)
		return (3);
	else if (ft_strcmp(str, "add\0") == 0)
		return (4);
	else if (ft_strcmp(str, "sub\0") == 0)
		return (5);
	else if (ft_strcmp(str, "and\0") == 0)
		return (6);
	else if (ft_strcmp(str, "or\0") == 0)
		return (7);
	else if (ft_strcmp(str, "xor\0") == 0)
		return (8);
	else if (ft_strcmp(str, "zjmp\0") == 0)
		return (9);
	else if (ft_strcmp(str, "ldi\0") == 0)
		return (10);
	else if (ft_strcmp(str, "sti\0") == 0)
		return (11);
	else
		return (is_inst_2(str));
}

int 	is_label(char *str)
{
	int 	i;
	int 	len;

	if (!str)
		exit(ft_printf("ERROR: last label points to nothing\n"));
	len = (int)ft_strlen(str);
	if (len < 2 || str[len - 1] != LABEL_CHAR)
		return (0);
	i = 0;
	while (i < len - 1)
	{
		if (ft_strchr(LABEL_CHARS, str[i]) == NULL)
			return (0);
		i++;
	}
	return (1);
}

void	get_next(t_label *label, t_data *data)
{
	char 	*str;

	while (get_clean_str(data, &str) && ft_strlen(str) < 1)
	{
		data->line++;
		free_str(&str, NULL, 1);
	}
	data->line++;
	label->pozz = get_labels(data, str);
	free_str(&str, NULL, 1);
}

int 	get_label(t_data *data, char **str, int str_len)
{
	t_label		*label;
	int 		label_place;

	label = set_label(&data->label, str[0]);
	label_place = label->pozz;
	if (str_len > 1 && is_label(str[1]))
		label->pozz = get_label(data, &str[1], str_len - 1);
	else if (str_len > 1 && is_instrctn(str[1]))
		label->pozz = get_instrctn(data, &str[1], is_instrctn(str[1]), str_len - 1);
	else if (str_len > 1)
		exit(ft_printf("ERROR: %s at line %d", str[1], data->line));
	else if (str_len < 2)
		get_next(label, data);
	label->pozz = (label_place == -1) ? label->pozz : label_place;
	return (label->pozz);
}