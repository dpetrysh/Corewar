/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_ncurs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleksiu <soleksiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 22:34:31 by soleksiu          #+#    #+#             */
/*   Updated: 2018/12/28 22:34:32 by soleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_make_height(t_c *data)
{
	data->height = MEM_SIZE / 64;
	if ((double)data->height < sqrt(MEM_SIZE))
		data->height++;
}

static	void		vm_print_side(int x, int y, int len, char direction)
{
	int	i;

	i = 0;
	attron(COLOR_PAIR(13));
	while (i <= len)
	{
		if (direction == 'h')
			mvprintw(y, x + i, " ");
		else if (direction == 'v')
			mvprintw(y + i, x, " ");
		i++;
	}
	attron(COLOR_PAIR(13));
}

static void			vm_print_border(int x, int y, int width, int height)
{
	vm_print_side(x, y, width, 'h');
	vm_print_side(x, y + height, width, 'h');
	vm_print_side(x, y, height, 'v');
	vm_print_side(x + width, y, height, 'v');
	refresh();
}

static void			vm_init_colors(void)
{
	start_color();
	init_color(COLOR_WHITE, 420, 420, 420);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_GREEN);
	init_pair(7, COLOR_BLACK, COLOR_BLUE);
	init_pair(8, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(9, COLOR_BLACK, COLOR_RED);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	init_pair(11, COLOR_BLUE, COLOR_BLACK);
	init_pair(12, COLOR_BLACK, COLOR_YELLOW);
	init_pair(13, COLOR_BLACK, COLOR_CYAN);
	init_pair(14, COLOR_BLACK, COLOR_CYAN);
	init_pair(15, COLOR_BLACK, COLOR_CYAN);
	init_pair(16, COLOR_WHITE, COLOR_GREEN);
	init_pair(17, COLOR_WHITE, COLOR_BLUE);
	init_pair(18, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(19, COLOR_WHITE, COLOR_RED);
}

void				init_ncurs(t_c *data)
{
	data->wnd_ptr = initscr();
	vm_make_height(data);
	vm_init_colors();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	nodelay(data->wnd_ptr, true);
	if (data->fl & C_DEBUG)
		data->vis_delay = VISDELAYMIN;
	else
		data->vis_delay = (VISDELAYMAX - VISDELAYMIN) / 2;
	vm_print_border(1, 1, 257, data->height + 1);
	vm_print_border(262, 1, 38, 65);
}
