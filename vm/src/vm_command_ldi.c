/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_ldi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 18:36:03 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/12/25 18:36:04 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_command_ldi(t_c *c, t_pc *pc)
{
	t_uint			n;

	if (pc->args[0] == IND_CODE)
	{
		n = MOD(pc->map_pos + (short)pc->val[0] % IDX_MOD);
		pc->val[0] = c->map[n] << 24 | c->map[MOD(n + 1)] << 16 | \
			c->map[MOD(n + 2)] << 8 | c->map[MOD(n + 3)];
	}
	n = MOD(pc->map_pos + (pc->val[0] + pc->val[1]) % IDX_MOD);
	pc->reg[pc->val[2] - 1] = c->map[n] << 24 | c->map[MOD(n + 1)] << 16 | \
		c->map[MOD(n + 2)] << 8 | c->map[MOD(n + 3)];
}
