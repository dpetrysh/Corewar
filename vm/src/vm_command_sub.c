/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleksiu <soleksiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:27:46 by soleksiu          #+#    #+#             */
/*   Updated: 2018/12/21 20:27:47 by soleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_command_sub(t_c *data, t_pc *carriage)
{
	t_uint			minuend;
	t_uint			subtrahend;
	t_uint			*diff;

	(void)data;
	minuend = carriage->reg[carriage->val[0] - 1];
	subtrahend = carriage->reg[carriage->val[1] - 1];
	diff = &carriage->reg[carriage->val[2] - 1];
	*diff = minuend - subtrahend;
	carriage->carry = (*diff == 0) ? 1 : 0;
}
