/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_live.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleksiu <soleksiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 13:05:01 by soleksiu          #+#    #+#             */
/*   Updated: 2018/12/22 13:05:03 by soleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			vm_make_lastlive(t_c *data, int id)
{
	int i;

	i = -1;
	while (++i < data->ch_count)
	{
		if (id == data->ch[i]->index)
		{
			data->ch[i]->last_live = data->cycles_all + 1;
			data->ch[i]->lives++;
			data->winner_index = i;
			break ;
		}
	}
	if (!data->fl)
		ft_printf("A process shows that player %d (%s) is alive.\n",
			data->ch[i]->index, data->ch[i]->name);
}

void				vm_command_live(t_c *data, t_pc *carriage)
{
	int				player_nb;
	short			code_for_visu;
	short			counter_for_visu;

	counter_for_visu = 50;
	carriage->alive = 1;
	player_nb = (short)carriage->val[0] * (-1);
	if (player_nb == carriage->bot_id)
	{
		code_for_visu = data->map_index[carriage->map_pos] & 7;
		counter_for_visu = counter_for_visu << 3;
		code_for_visu = code_for_visu | counter_for_visu;
		code_for_visu |= (1 << 9);
		data->map_index[carriage->map_pos] = code_for_visu;
		data->ps_alive_nb++;
		carriage->alive = 1;
		vm_make_lastlive(data, carriage->bot_id);
	}
}
