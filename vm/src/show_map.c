/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrysh <dpetrysh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:41:21 by dpetrysh          #+#    #+#             */
/*   Updated: 2018/11/30 12:41:22 by dpetrysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_display_speed(t_c *data)
{
	int				i;
	int				dot_nb;
	float			speed;

	i = 0;
	speed = 100.0 - ((100.0 * data->vis_delay) / (VISDELAYMAX - VISDELAYMIN));
	speed += speed <= 0 ? 1 : 0;
	mvprintw(4, 265, "Game speed: %3.0f%%", speed);
	mvprintw(5, 265, "[                              ]");
	dot_nb = (speed / 3) - 1;
	dot_nb += dot_nb == 0 ? 1 : 0;
	if (dot_nb > 30)
		dot_nb = 30;
	attron(COLOR_PAIR(12));
	while (i < dot_nb)
	{
		mvprintw(5, 266 + i, " ");
		i++;
	}
	attroff(COLOR_PAIR(12));
}

static void			vm_pause(t_c *data)
{
	while (data->pause)
	{
		attron(A_BOLD);
		if (data->game_running == 0)
			mvprintw(2, 265, "Game status: %s", "FINISHED");
		else
			mvprintw(2, 265, "Game status: %s", \
				data->fl & C_DEBUG ? "DEBUGGING MODE" : "PAUSED ");
		attron(A_BOLD);
		if (!(data->fl & C_DEBUG))
			vm_display_speed(data);
		vm_keys_handler(data);
		usleep(data->vis_delay);
	}
}

static void			vm_print_controls_menu(t_c *data)
{
	attron(A_BOLD);
	attron(COLOR_PAIR(11));
	mvprintw(data->height + 4, 2, "Q.......quit");
	if (!(data->fl & C_DEBUG))
	{
		mvprintw(data->height + 5, 2, "P.......pause/resume");
		mvprintw(data->height + 6, 2, "E.......increase speed");
		mvprintw(data->height + 7, 2, "W.......decrease speed");
	}
	if (data->fl & C_DEBUG)
		mvprintw(data->height + 4, 118,
		"Press 'SPACE' to move to the next cycle");
	attroff(11);
	attroff(A_BOLD);
}

static void			vm_make_pause(t_c *data)
{
	if (data->pause)
		vm_pause(data);
	usleep(data->vis_delay);
	if (data->fl & C_DEBUG)
		data->pause = 1;
}

void				show_map(t_c *data, t_uch *map, short *index)
{
	(void)map;
	(void)index;
	vm_print_controls_menu(data);
	vm_keys_handler(data);
	vm_show_nodes(data, data->map, data->map_index, data->height);
	vm_display_carriages(data);
	vm_show_info(data);
	vm_make_pause(data);
	refresh();
}
