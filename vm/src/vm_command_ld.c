/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_ld.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 23:44:15 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/12/24 23:44:16 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_command_ld(t_c *c, t_pc *pc)
{
	t_uint			n;

	if (pc->args[0] == DIR_CODE)
		pc->reg[pc->val[1] - 1] = pc->val[0];
	else if (pc->args[0] == IND_CODE)
	{
		n = MOD(pc->map_pos + pc->val[0] % IDX_MOD);
		pc->reg[pc->val[1] - 1] = c->map[n] << 24 | c->map[MOD(n + 1)] << 16 | \
			c->map[MOD(n + 2)] << 8 | c->map[MOD(n + 3)];
	}
	pc->carry = (pc->reg[pc->val[1] - 1] ? 0 : 1);
}
