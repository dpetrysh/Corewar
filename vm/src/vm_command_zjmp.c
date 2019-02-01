/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_zjmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleksiu <soleksiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 14:57:02 by soleksiu          #+#    #+#             */
/*   Updated: 2018/12/22 14:57:03 by soleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_command_zjmp(t_c *data, t_pc *carriage)
{
	short				jmp_val;

	(void)data;
	jmp_val = (short)carriage->val[0] % IDX_MOD;
	carriage->map_pos += carriage->carry ? jmp_val : 3;
}
