//
// Created by И Б on 16.05.20.
//

#include "asm.h"

int		on_line(char *str)
{
	int 	i;
	int 	counter;

	i = (int)ft_strlen(str);
	counter = 0;
	while (i > 0 && counter < 2)
	{
		i--;
		if (str[i] == '"')
			counter++;
	}
	if (counter > 1)
		return (1);
	else if (counter > 0)
		return (0);
	else
		return (-1);
}

void	add_line(char **str)
{
	char 	*tmp;

	tmp = ft_strjoin(*str, "\n");
	free_str(str, NULL, 1);
	*str = tmp;
}

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
		exit(ft_printf("ERROR, no quotes (line %d)\n ", data->line));
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

void	get_labels(t_data *data, char *str)
{
	exit(printf("lol"));
}