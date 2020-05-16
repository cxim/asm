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