//
// Created by И Б on 16.05.20.
//

#ifndef ASM_ASM_H
#define ASM_ASM_H

#include "ft_printf/includes/printf.h"
#include "op.h"

# define ALT_COMMENT_C ';'
# define MAX_ARG 3
# define A 200
# define B 610
# define C 150
# define D 111
# define E 111
# define F 771
# define G 771
# define H 771
# define I 200
# define J 731
# define K 173
# define L 200
# define M 610
# define N 731
# define O 200
# define P 100
# define ARGS_QTY_SIZE (int[]){0, 1, 2, 2, 3, 3, 3, 3, 3, 1, 3, 3, 1, 2, 3, 1, 1}
# define ARGS_TYPES (int[]){0, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P}
# define OCTAL (int[]){0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1}

typedef struct		s_oper
{
	int 			unq_id;
	int 			instrctn_id;
	int 			pozz;
	int 			octet;
	int 			argum[3];
	int 			argum_type[3];
	int 			argum_is_label[3];
	int 			argum_size[3];
	int 			size;
	struct s_oper	*next;
}					t_oper;

typedef struct 		s_label
{
	int 			id;
	int 			pozz;
	char 			*name;
	struct s_label	*next;
}					t_label;

typedef struct		s_data
{
	int 			fd_r;
	int 			fd_w;
	int 			total;
	char 			*name;
	char 			*comment;
	unsigned 		line;
	struct s_label	*label;
	struct s_oper	*op;
}					t_data;

/*
 * внести структы операц + меток
 */




int 	get_clean_str(t_data *data, char **str);
void	free_str(char **s, char ***arr, int i);
void	choose_do(t_data *data, char *tmp);
void	get_name_comment(t_data *data, char *str, int flag);
int		get_labels(t_data *data, char *str);
char 	*add_spaces(char **str);
char	**ft_strsplit_whitespace(char const *s);
void	add_line(char **str);
int		on_line(char *str);
int 	is_label(char *str);
int 	get_label(t_data *data, char **str, int str_len);
t_label	*set_label(t_label **label, char *str);
int 	is_instrctn(char *str);
int 	get_instrctn(t_data *data, char **str, int inst_id, int id);
void	set_oper_size(t_oper *op);
t_oper	*set_instrctn(t_data *data, int inst_id, int op_id);
int 	get_argums(t_oper *op, char **argv, int argc, t_data *data);

#endif //ASM_ASM_H
