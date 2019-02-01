/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args_parce.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 18:39:40 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/12/25 18:39:42 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_uint		vm_get_reg(t_c *c, t_pc *pc, t_uint n)
{
	t_uint			k;

	(void)pc;
	k = c->map[n];
	if (k > 0 && k < 17)
		return (k);
	else
		return (-1);
}

static t_uint		vm_get_dir(t_c *c, t_pc *pc, t_uint n)
{
	if (pc->cur_op->label_size == 2)
		return (c->map[n] << 8 | c->map[MOD(n + 1)]);
	else
		return (c->map[n] << 24 | c->map[MOD(n + 1)] << 16 | \
			c->map[MOD(n + 2)] << 8 | c->map[MOD(n + 3)]);
}

static t_uint		vm_get_ind(t_c *c, t_pc *pc, t_uint n)
{
	t_uint			m;

	m = MOD(pc->map_pos + (c->map[n] << 8 | c->map[MOD(n + 1)]) % IDX_MOD);
	if (pc->cur_op->op > 5 && pc->cur_op->op < 9)
		return (c->map[m] << 24 | c->map[MOD(m + 1)] << 16 | \
				c->map[MOD(m + 2)] << 8 | c->map[MOD(m + 3)]);
	else
		return (c->map[n] << 8 | c->map[MOD(n + 1)]);
}

static void			vm_init_get(t_uint (*ft_get[4])(t_c *c, t_pc *pc, t_uint n))
{
	ft_get[1] = vm_get_reg;
	ft_get[2] = vm_get_dir;
	ft_get[3] = vm_get_ind;
}

short				vm_get_args(t_c *c, t_pc *pc)
{
	t_uint			i;
	short			k;
	t_uint			(*ft_get[4])(t_c *c, t_pc *pc, t_uint n);

	i = pc->cur_op->codage;
	if (!pc->cur_op->codage)
	{
		vm_get_dir_no_codage(c, pc);
		return (1);
	}
	k = -1;
	vm_init_get(ft_get);
	while (++k < 3 && pc->args[k])
	{
		pc->val[k] = ft_get[(short)pc->args[k]](c, pc, pc->map_pos + i + 1);
		if (pc->val[k] == -1 && pc->args[k] == REG_CODE)
			return (0);
		if (pc->args[k] == REG_CODE)
			i++;
		else if (pc->args[k] == DIR_CODE)
			i += pc->cur_op->label_size;
		else if (pc->args[k] == IND_CODE)
			i += 2;
	}
	return (1);
}
