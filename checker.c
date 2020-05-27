//
// Created by И Б on 24.05.20.
//

#include "asm.h"

void	check_size(t_oper *op)
{
	int		size;
	int		i;

	size = 1;
	size += (op->octet != 0);
	i = 0;
	while (i < MAX_ARG)
	{
		if (op->argum_type[i] < 0)
			exit(ft_printf("ERROR: negativ type for oper. %d\n", op->unq_id));
		if (op->argum_type[i] == 0 && (op->argum_type[i] < 1 || op->argum_type[i] > 99))
			exit(ft_printf("ERROR: invalid registr value for op. %d\n", op->unq_id));
		if (op->argum_type[i] == 1)
			size++;
		if (op->argum_type[i] == 2)
			size += T_DIR_SIZE[op->instrctn_id];
		else if (op->argum_type[i] == 3)
			size += 2;
		i++;
	}
	if (size != op->size)
		exit(ft_printf("ERROR: wrong OPsize, oper. %d\n", op->unq_id));
}

void    check_lbls(t_oper *op, t_label *lb, int i)
{
	t_label		*tmp;

	tmp = lb;
	if ((op->argum_is_label[i] != 0 && op->argum_type[i] > 0) || (op->argum_is_label[i] == 0 && op->argum_type[i] < 0))
		exit(ft_printf("ERROR: incompatible arg-lbl combination\n"));
	else if (op->argum_type[i] < 0)
		op->argum_type[i] = -op->argum_type[i];
	while (tmp != NULL && tmp->id != op->argum_type[i])
		tmp = tmp->next;
	if (tmp == NULL)
		exit(ft_printf("ERROR: label %d for oper. %d not found!\n", op->argum_is_label[i], op->unq_id));
	if (tmp->pozz == -1)
		exit(ft_printf("ERROR: label %s not found!\n", tmp->name));
	op->argum[i] = tmp->pozz - op->pozz;
	if (op->argum_type[i] == 1 && (op->argum_type[i] > 99 || op->argum[i] < 1))
		exit(ft_printf("ERROR: oper %d arg %d is reg %d - invalid", op->unq_id, i, op->argum[i]));
}

void	check_arg(t_oper *op, t_label *label)
{
	int 	i;
	int 	args;
	int 	allowed;

	i = MAX_ARG;
	args = ARGS_QTY_SIZE[op->instrctn_id];
	allowed = ARGS_TYPES[op->instrctn_id];
	while (i > args)
	{
		i--;
		if (op->argum_type[i] != 0)
			exit(ft_printf("ERROR: too many arg for instrctn nb %d\n", op->unq_id));
		allowed /= 10;
	}
	while (i > 0)
	{
		i--;
		if (op->argum_type[i] < 0 || op->argum_is_label[i] != 0)
			check_lbls(op, label, i);
		if ((allowed % 10) != 0 && ((allowed % 10) & (op->argum_type[i] + (op->argum_type[i] > 2))) == 0)
			exit(ft_printf("ERROR: invalid arg type\n"));
		allowed /= 10;
	}
}

void	check_op(t_data *data, t_oper *op)
{
	if (op->instrctn_id > 16 || op->instrctn_id < 1)
		exit(ft_printf("ERROR: instrctn id %d for operation nb %d is invalid\n", op->instrctn_id, op->unq_id));
	if (op->unq_id < 1)
		exit(ft_printf("ERROR: id for operation nb %d is invalid\n", op->unq_id));
	if (op->next && op->unq_id - op->next->unq_id != -1)
		exit(ft_printf("ERROR: operation %d enumeration sequence is wrong\n", op->unq_id));
	if (op->pozz >= data->total)
		exit(ft_printf("ERROR: operation nb %d pozz is wrong\n", op->unq_id));
	op->octet *= OCTAL[op->instrctn_id];
}

void	check_all(t_data *data)
{
	t_oper	*op;
	t_label	*label;

	if (!data->name)
		exit(ft_printf("ERROR: Champ name dont set\n"));
	if (!data->comment)
		exit(ft_printf("ERROR: Champ comment dont set\n"));
	if (!data->op)
		exit(ft_printf("ERROR: Champ has no instrctns\n"));
	if (ft_strlen(data->name) > PROG_NAME_LENGTH)
		exit(ft_printf("ERROR: .name too long (%d) > max len (%d)\n", ft_strlen(data->name), PROG_NAME_LENGTH));
	if (ft_strlen(data->comment) > COMMENT_LENGTH)
		exit(ft_printf("ERROR: .comment too long (%d) > max len (%d)\n", ft_strlen(data->comment), COMMENT_LENGTH));
	op = data->op;
	while (op)
	{
		check_op(data, op);
		label = data->label;
		check_arg(op, label);
		check_size(op);
		op = op->next;
	}
}