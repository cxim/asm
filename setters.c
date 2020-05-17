//
// Created by И Б on 17.05.20.
//

#include "asm.h"

t_oper		*set_instrctn(t_data *data, int inst_id, int op_id)
{
	t_oper	*op;

	op = data->op;
	while (op != NULL && op->next != NULL)
	{
		op_id++;
		op = op->next;
	}
	if (op == NULL)
	{
		data->op = (t_oper*)ft_memalloc(sizeof(t_oper));
		op = data->op;
	}
	else
	{
		op->next = (t_oper*)ft_memalloc(sizeof(t_oper));
		op_id++;
		op = op->next;
	}
	op->instrctn_id = inst_id;
	op->unq_id = op_id;
	op->pozz = data->total;
	return (op);
}

void		set_oper_size(t_oper *op)
{
	int 	i;
	i = 0;
	op->size = 1;
	while (i < 3)
	{
		op->size += op->argum_size[i];
		i++;
	}
	op->size += (op->octet != 0);
}


void		set_new_l(t_label **head, char *str, int id)
{
	head[0] = (t_label*)ft_memalloc(sizeof(t_label));
	head[0]->name = ft_strdup(str);
	head[0]->id = id;
	head[0]->pozz = -1;
}

t_label		*set_label(t_label **label, char *str)
{
	t_label		*ret;
	t_label		*tmp;
	int 		id;

	id = 1;
	ret = *label;
	if (ft_strlen(str) > 0)
		str[ft_strlen(str) - 1] = 0;
	while (ret != NULL && ret->next != NULL && ft_strcmp(ret->name, str) != 0)
	{
		id++;
		ret = ret->next;
	}
	if (ret != NULL && ft_strcmp(ret->name, str) == 0)
		return (ret);
	if (ret != NULL)
		id++;
	set_new_l(&tmp, str, id);
	if (ret == NULL)
		*label = tmp;
	else
		ret->next = tmp;
	return (tmp);
}