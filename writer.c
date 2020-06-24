//
// Created by cxim1 on 28.05.2020.
//

#include "asm.h"

void 	write_rev(int fd, unsigned char *str, unsigned length)
{
	while (length > 0)
	{
		length--;
		write(fd, &str[length], 1);
	}
}

void 	write_n_and_c(int fd, char *str, unsigned len_macro)
{
	int		len;
	char 	*zero;

	len = (int)ft_strlen(str);
	zero = (char*)ft_memalloc(sizeof(char) * (len_macro - len + 1));
	write(fd, str, len);
	write(fd, zero, (len_macro - len));
	free_str(&zero, NULL, 1);
}

void 	select_type(int fd, t_oper *op, int arg_n)
{
	unsigned char	c;
	unsigned char 	s;
	unsigned char 	i;

	if (op->argum_type[arg_n] == 1)
	{
		c = (unsigned char)op->argum[arg_n];
		write_rev(fd, (unsigned char*)(&c), sizeof(c));
	}
	else if (op->argum_type[arg_n] == 2 && T_DIR_SIZE[op->instrctn_id] == 4)
	{
		i = (unsigned int)op->argum[arg_n];
		write_rev(fd, (unsigned char *)(&i), sizeof(i));
	}
	else
	{
		s = (unsigned char)op->argum[arg_n];
		write_rev(fd, (unsigned char*)(&s), sizeof(s));
	}
}

void 	write_op(int fd, t_oper *op)
{
	unsigned char	c;
	int 			i;

	c = (unsigned char)op->instrctn_id;
	write_rev(fd, (unsigned char*)(&c), sizeof(c));
	if (op->octet != 0)
	{
		c = (unsigned char)op->octet;
		write_rev(fd, (unsigned char*)(&c), sizeof(c));
	}
	i = 0;
	while (i < ARGS_QTY_SIZE[op->instrctn_id])
	{
		select_type(fd, op, i);
		i++;
	}
}

void 	write_file(t_data * data)
{
	int 	magic;
	int		zero;
	t_oper	*op;

	magic = COREWAR_EXEC_MAGIC;
	zero = 0;
	write_rev(data->fd_w, (unsigned char *)(&magic), sizeof(int));
	write_n_and_c(data->fd_w, data->name, PROG_NAME_LENGTH);
	write(data->fd_w, (unsigned char*)(&zero), sizeof(int));
	write_rev(data->fd_w, (unsigned char*)(&data->total), sizeof(int));
	write_n_and_c(data->fd_w, data->comment, COMMENT_LENGTH);
	write(data->fd_w, (unsigned char *)(&zero), sizeof(int));
	op = data->op;
	while (op != NULL)
	{
		write_op(data->fd_w, op);
		op = op->next;
	}
}