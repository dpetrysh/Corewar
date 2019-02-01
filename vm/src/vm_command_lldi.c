/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_lldi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 21:05:54 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/12/25 21:05:55 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_command_lldi(t_c *c, t_pc *pc)
{
	t_uint			n;

	if (pc->args[0] == IND_CODE)
	{
		n = MOD(pc->map_pos + pc->val[0] % IDX_MOD);
		pc->val[0] = c->map[n] << 24 | c->map[MOD(n + 1)] << 16 | \
			c->map[MOD(n + 2)] << 8 | c->map[MOD(n + 3)];
	}
	n = MOD(pc->map_pos + pc->val[0] + pc->val[1]);
	pc->reg[pc->val[2] - 1] = c->map[n] << 24 | c->map[MOD(n + 1)] << 16 | \
		c->map[MOD(n + 2)] << 8 | c->map[MOD(n + 3)];
	pc->carry = (pc->reg[pc->val[2] - 1] ? 0 : 1);
}
