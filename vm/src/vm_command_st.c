/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_sti_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrysh <dpetrysh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:47:20 by dpetrysh          #+#    #+#             */
/*   Updated: 2018/12/18 16:47:21 by dpetrysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			vm_get_ind(t_c *data, int cur_pos)
{
	short			dir_value;
	short			first_byte;
	short			scnd_byte;

	dir_value = 0;
	first_byte = data->map[MOD(cur_pos + 3)];
	scnd_byte = data->map[MOD(cur_pos + 4)];
	dir_value = scnd_byte | (first_byte << 8);
	return (dir_value);
}

static void			vm_put_value(t_c *data, int cur_pos, unsigned int value)
{
	data->map[MOD((t_uint)cur_pos)] = (value & 0xFF000000) >> 24;
	data->map[MOD((t_uint)cur_pos + 1)] = (value & 0x00FF0000) >> 16;
	data->map[MOD((t_uint)cur_pos + 2)] = (value & 0x0000FF00) >> 8;
	data->map[MOD((t_uint)cur_pos + 3)] = (value & 0x000000FF);
}

static void			vm_put_indexes(t_c *data, int cur_pos, int bot_id)
{
	short	counter;

	counter = 50;
	counter = counter << 3;
	data->map_index[MOD((t_uint)cur_pos)] = bot_id;
	data->map_index[MOD((t_uint)cur_pos + 1)] = bot_id;
	data->map_index[MOD((t_uint)cur_pos + 2)] = bot_id;
	data->map_index[MOD((t_uint)cur_pos + 3)] = bot_id;
	data->map_index[MOD((t_uint)cur_pos)] |= counter;
	data->map_index[MOD((t_uint)(cur_pos + 1))] |= counter;
	data->map_index[MOD((t_uint)(cur_pos + 2))] |= counter;
	data->map_index[MOD((t_uint)(cur_pos + 3))] |= counter;
}

void				vm_command_st(t_c *data, t_pc *crg)
{
	int				first;

	first = crg->reg[crg->val[0] - 1];
	if (crg->args[1] == 1)
		crg->reg[crg->val[1] - 1] = first;
	else if (crg->args[1] == 3)
	{
		crg->val[1] = vm_get_ind(data, crg->map_pos);
		vm_put_value(data, crg->map_pos + (short)crg->val[1] % IDX_MOD, first);
		vm_put_indexes(data, crg->map_pos + (short)crg->val[1] % IDX_MOD, \
			crg->bot_id);
	}
}
