//
// Created by И Б on 16.05.20.
//

#include "asm.h"

int 	get_clean_str(t_data *data, char **str)
{
	char 	*s;
	char 	*tmp;
	int 	ret;
	char 	**arr;

	ret = get_next_line(data->fd_r, &s);
	tmp = ft_strtrim(s);
	printf("%s\n", s);
	printf("%s\n", s);
	free_str(&s, NULL, 1);
	if (tmp == NULL || ft_strlen(tmp) == 0)
	{
		*str = ft_strdup("");
		free_str(&tmp, NULL, 1);
		return (ret);
	}
	arr = 0;
	if (tmp[0] == COMMENT_CHAR || tmp[0] == ALT_COMMENT_C)
		*str = ft_strdup("");
	else if (ft_strchr(tmp, COMMENT_CHAR))
		arr = ft_strsplit(tmp, COMMENT_CHAR);
	else
		arr = ft_strsplit(tmp, ALT_COMMENT_C);
	if (arr != 0 && ft_strlen(arr[0]) > 0)
		*str = ft_strdup(arr[0]);
	free_str(&tmp, &arr, 2);
	return (ret);
}

void	choose_do(t_data *data, char *tmp)
{
	char	**arr;

	if (ft_strchr(tmp, COMMENT_CHAR))
		arr = ft_split(tmp, COMMENT_CHAR);
	else
		arr = ft_split(tmp, ALT_COMMENT_C);
	if (ft_strlen(tmp) > 0 && tmp[0] != COMMENT_CHAR && tmp[0] != ALT_COMMENT_C)
	{
		if (ft_strncmp(arr[0], NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0)
			get_name_comment(data, arr[0], 1);
		else if (ft_strncmp(arr[0], COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) == 0)
			get_name_comment(data, arr[0], 2);
		else
			get_labels(data, arr[0]);
	}
	free_str(NULL, &arr, 0);
}