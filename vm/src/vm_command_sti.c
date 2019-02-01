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

static t_uint		vm_get_inddir(t_c *data, int cur_pos)
{
	t_uint			first_byte;
	t_uint			scnd_byte;
	t_uint			thrd_byte;
	t_uint			frth_byte;

	first_byte = data->map[MOD(cur_pos)] << 24;
	scnd_byte = data->map[MOD(cur_pos + 1)] << 16;
	thrd_byte = data->map[MOD(cur_pos + 2)] << 8;
	frth_byte = data->map[MOD(cur_pos + 3)];
	return (first_byte | scnd_byte | thrd_byte | frth_byte);
}

static void			vm_put_value(t_c *data, int cur_pos, unsigned int value)
{
	data->map[MOD((t_uint)cur_pos)] = (value & 0xFF000000) >> 24;
	data->map[MOD((t_uint)(cur_pos + 1))] = (value & 0x00FF0000) >> 16;
	data->map[MOD((t_uint)(cur_pos + 2))] = (value & 0x0000FF00) >> 8;
	data->map[MOD((t_uint)(cur_pos + 3))] = (value & 0x000000FF);
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

void				vm_command_sti(t_c *data, t_pc *crg)
{
	t_uint			first;

	first = crg->reg[crg->val[0] - 1];
	if (crg->args[1] == REG_CODE)
		crg->val[1] = crg->reg[crg->val[1] - 1];
	if (crg->args[2] == REG_CODE)
		crg->val[2] = crg->reg[crg->val[2] - 1];
	if (crg->args[1] == IND_CODE)
		crg->val[1] = vm_get_inddir(data, crg->map_pos + \
			(short)crg->val[1] % IDX_MOD);
	vm_put_value(data, crg->map_pos + (((short)crg->val[1] +
		(short)crg->val[2]) % IDX_MOD), first);
	vm_put_indexes(data, crg->map_pos + (((short)crg->val[1] +
		(short)crg->val[2]) % IDX_MOD), crg->bot_id);
}
