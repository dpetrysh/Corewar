/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_lfork.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleksiu <soleksiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 19:40:44 by soleksiu          #+#    #+#             */
/*   Updated: 2018/12/21 19:40:47 by soleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_command_lfork(t_c *data, t_pc *carriage)
{
	t_pc			*new_carriage;
	int				move_crg;

	move_crg = (short)carriage->val[0];
	ft_lstadd(&data->carriage_list, ft_lstnew(carriage, sizeof(t_pc)));
	new_carriage = data->carriage_list->content;
	new_carriage->map_pos = MOD(carriage->map_pos + move_crg);
	new_carriage->sleep = 0;
	data->total_crg_nb++;
	new_carriage->pc_id = data->total_crg_nb;
}
