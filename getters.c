//
// Created by И Б on 16.05.20.
//

#include "asm.h"



void	check_lenght(char *str, int flag)
{
	if (flag == 1 && ft_strlen(str) > PROG_NAME_LENGTH)
		exit(ft_printf("ERROR: .name too long (%d) > max len (%d)\n", ft_strlen(str), PROG_NAME_LENGTH));
	if (flag == 2 && ft_strlen(str) > COMMENT_LENGTH)
		exit(ft_printf("ERROR: .comment too long (%d) > max len (%d)\n", ft_strlen(str), COMMENT_LENGTH));
}

void	get_multi_lines(t_data *data, char **str, int flag)
{
	char 	*joiner;
	char 	*readder;
	char 	*quote_pos;

	while (get_next_line(data->fd_r, &readder))
	{
		quote_pos = ft_strchr(readder, '"');
		if (quote_pos != NULL)
			quote_pos[0] = 0;
		data->line++;
		if (ft_strstr(readder, NAME_CMD_STRING) || ft_strstr(readder, COMMENT_CMD_STRING))
			exit(ft_printf("ERROR: missing closing quote (line %d)\n", data->line - 1));
		joiner = ft_strjoin(*str, readder);
		free_str(str, NULL, 1);
		free_str(&readder, NULL, 1);
		*str = joiner;
		joiner = 0;
		check_lenght(*str, flag);
		if (quote_pos != NULL)
			break ;
		add_line(str);
	}
}

void	get_name_comment(t_data *data, char *str, int flag)
{
	char 	**tmp;
	int		line;

	tmp = ft_split(str, '"');
	line = on_line(str);
	if (line == -1)
		exit(ft_printf("ERROR, no quotes (line %d)\n", data->line));
	if (tmp[1])
		str = ft_strdup(tmp[1]);
	else
		str = ft_strdup("");
	if (line < 1)
		add_line(&str);
	if (line < 1)
		get_multi_lines(data, &str, flag);
	check_lenght(str, flag);
	if (flag == 1 && !data->name)
		data->name = str;
	else if (flag == 2 && !data->comment)
		data->comment = str;
	else
		exit(ft_printf("ERROR: redifinition of name or comment\n"));
	free_str(NULL, &tmp, 0);
}

int 	get_instrctn(t_data *data, char **str, int inst_id, int str_len)
{
	t_oper		*op;

	if (inst_id == 0)
		return (0);
	if (str_len < 2)
		exit(ft_printf("ERROR: no arguments in line %d\n", data->line));
	op = set_instrctn(data, inst_id, 1);
	//get_argums(op, &str[1], str_len - 1, data);
	set_oper_size(op);
	data->total += op->size;
	return (op->pozz);
}

int		get_labels(t_data *data, char *str)
{
	char 	**tmp;
	char 	*str_space;
	int		i;
	int		ret;

	str_space = add_spaces(&str);
	tmp = ft_strsplit_whitespace(str_space);
	free_str(&str_space, NULL, 1);
	i = 0;
	while (tmp[i])
		i++;
	ret = 0;
	if (is_label(tmp[0]))
		ret = get_label(data, tmp, i);
	else if (is_instrctn(tmp[0]) != 0)
		ret = get_instrctn(data, tmp, is_instrctn(tmp[0]), i);
	else if (str[0] != '#')
		exit(ft_printf("ERROR: could't read line %d (%s)\n", data->line, str));
	free_str(NULL, &tmp, 0);
	//exit(1);
	return (ret);
}