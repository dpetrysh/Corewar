/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_map_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 00:39:12 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/12/28 00:39:14 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			vm_display_carriage_params(t_c *data)
{
	int				i;
	t_pc			*carriage;

	i = -1;
	attron(A_BOLD);
	if (!data->carriage_list)
		return ;
	carriage = (t_pc *)data->carriage_list->content;
	if (data->map[carriage->map_pos] == 0)
		carriage->cur_op = NULL;
	mvprintw(41, 265, "Checks nb:         %5d", data->checks_nb);
	mvprintw(42, 265, "PS alive nb:       %5d", data->ps_alive_nb);
	mvprintw(43, 265, "Command execution: %5s", \
		carriage->cur_op ? carriage->cur_op->name : "none");
	mvprintw(44, 265, "Player id:         %5d", carriage->bot_id);
	mvprintw(45, 265, "Map position:      %5u", carriage->map_pos);
	mvprintw(46, 265, "Carry:             %5u", carriage->carry);
	mvprintw(47, 265, "Sleep:             %5u", carriage->sleep);
	mvprintw(48, 265, "Alive:             %5s", carriage->alive ? "yes" : "no");
	mvprintw(49, 265, "Registers content:");
	while (++i < REG_NUMBER)
		mvprintw(50 + i, 265, "%sr%d: %10x(%5hd)", \
			i < 9 ? " " : "", i + 1, carriage->reg[i], (short)carriage->reg[i]);
	attron(A_BOLD);
}

static void			vm_show_status(t_c *data)
{
	if (!(data->fl & C_DEBUG))
	{
		mvprintw(2, 265, "Game status: %s", "RUNNING");
		vm_display_speed(data);
	}
	mvprintw(7, 265, "Cycles : %d", data->cycles_all);
	mvprintw(9, 265, "Processes : %d", data->total_crg_nb);
}

static void			vm_show_info_in_end(t_c *data, int *pl_cord)
{
	if (data->game_running == 0)
	{
		mvprintw(*pl_cord + 18, 265, "The winner is : Player-%d \"",
			data->winner_index + 1);
		mvprintw(*pl_cord + 18, 291, "%s\"", \
			data->ch[data->winner_index]->name);
		mvprintw(*pl_cord + 19, 265, "Press 'Q' for exit");
	}
}

static void			vm_show_champ_info(t_c *data, int *pl_cord)
{
	int				i;

	i = -1;
	while (++i < data->ch_count)
	{
		*pl_cord += 5;
		mvprintw(*pl_cord + 1, 265, "Player -%d: %s",
			data->ch[i]->index, data->ch[i]->name);
		mvprintw(*pl_cord + 2, 265, "Last live : %21d", data->ch[i]->last_live);
		mvprintw(*pl_cord + 3, 265, "Lives in current period : %7d", \
			data->ch[i]->lives);
	}
}

void				vm_show_info(t_c *data)
{
	int	pl_cord;

	pl_cord = 10;
	attron(COLOR_PAIR(5));
	attron(A_BOLD);
	vm_show_status(data);
	vm_show_champ_info(data, &pl_cord);
	mvprintw(pl_cord + 7, 265, "CYCLE TO DIE : %d   ",
		data->cycle_to_die > 0 ? data->cycle_to_die : 0);
	mvprintw(pl_cord + 9, 265, "CYCLE DELTA : %d", CYCLE_DELTA);
	mvprintw(pl_cord + 11, 265, "NBR_LIVE : %d", NBR_LIVE);
	mvprintw(pl_cord + 13, 265, "MAX_CHECKS : %d", MAX_CHECKS);
	vm_show_info_in_end(data, &pl_cord);
	attroff(A_BOLD);
	attroff(5);
	if (data->fl & C_DEBUG && data->cycles_all != 0)
		vm_display_carriage_params(data);
}
