/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleksiu <soleksiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:33:13 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/12/13 15:12:19 by soleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			vm_get_argsize(t_op *cur_op, char arg)
{
	if (arg == T_REG)
		return (1);
	else if (arg == T_IND)
		return (2);
	else if (arg == T_DIR)
		return (cur_op->label_size);
	return (0);
}

static int			vm_check_arg(char define, char cur_arg)
{
	char			arg;

	arg = (cur_arg == 3) ? 4 : cur_arg;
	return (define & arg);
}

void				vm_read_codage(unsigned char n, char ar[3])
{
	ar[0] = (n & 192) >> 6;
	ar[1] = (n & 48) >> 4;
	ar[2] = (n & 12) >> 2;
}

void				vm_get_dir_no_codage(t_c *data, t_pc *crg)
{
	t_uint			dir_value;
	int				pos;

	pos = crg->map_pos;
	if (crg->cur_op->label_size == 4)
		dir_value = (data->map[pos + 4]) | (data->map[pos + 3] << 8) |
			(data->map[pos + 2] << 16) | (data->map[pos + 1] << 24);
	else
		dir_value = (data->map[pos + 2]) | (data->map[pos + 1] << 8);
	crg->val[0] = dir_value;
}

int					vm_args_validate(t_pc *crg, int *skip)
{
	int				i;
	int				ret;
	int				temp;

	i = -1;
	ret = 1;
	temp = 0;
	*skip = crg->cur_op->codage + 1;
	if (!crg->cur_op->codage)
	{
		*skip += crg->cur_op->label_size;
		return (1);
	}
	while (++i < crg->cur_op->nargs)
	{
		if (!(temp = vm_check_arg(crg->cur_op->args[i], crg->args[i])))
			ret = 0;
		*skip += vm_get_argsize(crg->cur_op, temp);
	}
	return (ret);
}
