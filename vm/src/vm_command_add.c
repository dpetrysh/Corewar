/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleksiu <soleksiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:27:38 by soleksiu          #+#    #+#             */
/*   Updated: 2018/12/21 20:27:39 by soleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_command_add(t_c *data, t_pc *carriage)
{
	t_uint			addend1;
	t_uint			addend2;
	t_uint			*sum;

	(void)data;
	addend1 = carriage->reg[carriage->val[0] - 1];
	addend2 = carriage->reg[carriage->val[1] - 1];
	sum = &carriage->reg[carriage->val[2] - 1];
	*sum = addend1 + addend2;
	carriage->carry = (*sum == 0) ? 1 : 0;
}
