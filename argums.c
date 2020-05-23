//
// Created by student on 20.0

#include "asm.h"

int 	only_allowed_chars(char *allowed_str, char *arg)
{
	int 	i;
	int 	len;

	i = 0;
	len = (int)ft_strlen(arg);
	while (i < len)
	{
		if (!ft_strchr(allowed_str, arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int 	check_type_in(char *arg)
{
	int 	ret;

	ret = 0;
	if (only_allowed_chars(ALLOWED_CHARS_ARG, arg) == 0)
		return (0);
	else if (arg[0] == 'r' && arg[1] != ':')
		ret = 1;
	else if (arg[0] == 'r' && arg[1] == ':')
		ret = -1;
	else if (arg[0] == '%' && arg[1] != ':')
		ret = 2;
	else if (arg[0] == '%' && arg[1] == ':')
		ret = -2;
	else if (ft_isdigit(arg[0]) || arg[0] == '-')
		ret = 3;
	else if (arg[0] == ':')
		ret = -3;
	if ((ret == 1 && only_allowed_chars(ALLOWED_CHARS_DIR, &arg[1]) == 0) || (ret == 2 && only_allowed_chars(ALLOWED_CHARS_DIR, &arg[1]) == 0)
		|| (ret == 3 && only_allowed_chars(ALLOWED_CHARS_DIR, arg) == 0))
		return (0);
	return (ret);

}

void	set_arg_val(t_oper *op, char *arg, int arg_nb, int arg_type)
{
	int 	flag;
	t_data	*data;

	data = get_data(NULL);
	if (arg_type == 1 || arg_type == 2)
		flag = 1;
	else
		flag = 2;
	if (arg_type > 0 && (ft_strlen(&arg[flag]) < 1 || (arg[flag] == '-' && (ft_strlen(&arg[flag]) < 2 || ft_strlen(&arg[flag]) > 11)) ||
		ft_strlen(&arg[flag]) > 10))
		exit(ft_printf("ERROR: argum '%s' is invalid (line %d)\n", arg, data->line));
	op->argum[arg_nb] = ft_atoi(&arg[flag]) * (arg_type > 0);
	if (arg_type < 0)
		arg_type = -arg_type;
	op->octet = op->octet | (arg_type << (6 - 2 * arg_nb));
	if (arg_type == 1 || arg_type == -1)
		op->argum_size[arg_nb] = 1;
	else if (arg_type == 3 || arg_type == -3)
		op->argum_size[arg_nb] = 2;
	else if (arg_type == 2 || arg_type == -2)
		op->argum_size[arg_nb] = T_DIR_SIZE[op->instrctn_id];
}

int		set_arg(t_oper *op, char *arg, int arg_nb, int allowed_t)
{
	int 	arg_type;
	int 	aux;
	char 	*tmp;
	t_data	*data;
	t_label	*label;

	arg_type = check_type_in(arg);
	aux = (arg_type > 2) + (-1) * (arg_type < -2);
	if (arg_type == 0 || ((arg_type + aux) & allowed_t) == 0 || (arg_type == -1 && only_allowed_chars(LABEL_CHARS, &arg[2]) == 0)
		|| (arg_type == -2 && only_allowed_chars(LABEL_CHARS, &arg[2]) == 0) || (arg_type == -3 && only_allowed_chars(LABEL_CHARS, &arg[1]) == 0))
		return (-1);
	if (arg_type < 0)
	{
		tmp = ft_strjoin(&arg[1 + (arg_type > -3)], ":\0");
		data = get_data(NULL);
		label = set_label(&data->label, tmp);
		op->argum_is_label[arg_nb] = label->id;
		free_str(&tmp, NULL, 1);
	}
	set_arg_val(op, arg, arg_nb, arg_type);
	op->argum_type[arg_nb] = arg_type;
	return (0);
}

int		set_argums(t_oper *op, char **clean_str, int allowed_t, int args_qty_s)
{
	int 	i;

	i = 0;
	while (i + args_qty_s < MAX_ARG)
	{
		allowed_t /= 10;
		i++;
	}
	while (args_qty_s > 0)
	{
		args_qty_s--;
		if (set_arg(op, clean_str[args_qty_s], args_qty_s, allowed_t % 10) < 0)
			return (-1);
		allowed_t /= 10;
	}
	return (1);
}

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
	i = 0;
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
	i = 0;
	while (clean_str[i] != NULL)
		i++;
	args_qty_size = ARGS_QTY_SIZE[op->instrctn_id];
	if (i != args_qty_size)
		exit(ft_printf("ERROR: wrong argum amount (line %d)\n", data->line));
	allowed_types = ARGS_TYPES[op->instrctn_id];
	if (set_argums(op, clean_str, allowed_types, args_qty_size) < 0)
		exit(ft_printf("ERROR: an argum is not valid(line %d)\n", data->line));
	op->octet *= OCTAL[op->instrctn_id];
	free_str(NULL, &clean_str, 0);
	return 0;
}