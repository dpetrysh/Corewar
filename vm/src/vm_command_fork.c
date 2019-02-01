/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleksiu <soleksiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:47:46 by soleksiu          #+#    #+#             */
/*   Updated: 2018/12/19 19:47:49 by soleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_command_fork(t_c *data, t_pc *carriage)
{
	t_pc			*new_carriage;
	int				move_crg;

	move_crg = (short)carriage->val[0];
	move_crg %= IDX_MOD;
	ft_lstadd(&data->carriage_list, ft_lstnew(carriage, sizeof(t_pc)));
	new_carriage = data->carriage_list->content;
	new_carriage->map_pos = MOD((t_uint)(carriage->map_pos + move_crg));
	new_carriage->sleep = 0;
	data->total_crg_nb++;
	new_carriage->pc_id = data->total_crg_nb;
}
