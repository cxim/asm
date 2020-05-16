//
// Created by И Б on 16.05.20.
//

#ifndef ASM_ASM_H
#define ASM_ASM_H

#include "ft_printf/includes/printf.h"
#include "op.h"

# define ALT_COMMENT_C ';'

typedef struct		s_data
{
	int 			fd_r;
	int 			fd_w;
	int 			total;
	char 			*name;
	char 			*comment;
	unsigned 		line;
}					t_data;

/*
 * внести структы операц + меток
 */




int 	get_clean_str(t_data *data, char **str);
void	free_str(char **s, char ***arr, int i);

#endif //ASM_ASM_H
