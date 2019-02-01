/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_map_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 00:35:08 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/12/28 00:35:10 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			vm_get_coords(int *x, int *y, int carriage_pos)
{
	if (!carriage_pos)
	{
		*x = 3;
		*y = 2;
		return ;
	}
	*x = carriage_pos % 64 * 4 + 3;
	*y = carriage_pos / 64 + 2;
}

static void			vm_display_node(t_c *data, int x, int y, int node)
{
	data->cnt ? attron(A_BOLD) : 0;
	attron(COLOR_PAIR(data->attr));
	mvprintw(y, x, "%02hhx ", node);
	attroff(data->attr);
	data->cnt ? attroff(A_BOLD) : 0;
}

static char			vm_get_attr_value(short map_val, char type)
{
	char	attr;

	attr = 5;
	if ((map_val & 7) == 1 && type == 'c')
		attr = 6;
	else if ((map_val & 7) == 2 && type == 'c')
		attr = 7;
	else if ((map_val & 7) == 3 && type == 'c')
		attr = 8;
	else if ((map_val & 7) == 4 && type == 'c')
		attr = 9;
	else if (type == 'c')
		attr = 10;
	else if ((map_val & 7) == 1 && type == 'm')
		attr = 1;
	else if ((map_val & 7) == 2 && type == 'm')
		attr = 2;
	else if ((map_val & 7) == 3 && type == 'm')
		attr = 3;
	else if ((map_val & 7) == 4 && type == 'm')
		attr = 4;
	else if (type == 'm')
		attr = 5;
	return (attr);
}

void				vm_display_carriages(t_c *data)
{
	int				carriage_pos;
	t_list			*list_pt;
	int				x;
	int				y;

	list_pt = data->carriage_list;
	x = 0;
	y = 0;
	while (list_pt)
	{
		carriage_pos = ((t_pc *)list_pt->content)->map_pos;
		vm_get_coords(&x, &y, carriage_pos);
		data->cnt = data->map_index[carriage_pos] >> 3;
		data->attr = vm_get_attr_value(data->map_index[carriage_pos], 'c');
		data->attr += (data->cnt) ? 10 : 0;
		vm_display_node(data, x, y, data->map[carriage_pos]);
		list_pt = list_pt->next;
	}
}

void				vm_show_nodes(t_c *d, t_uch *map, short *ind, int height)
{
	int				i;
	int				j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < 64)
		{
			if (j + i * 64 >= MEM_SIZE)
				return ;
			d->cnt = ind[j + i * 64] >> 3;
			d->attr = vm_get_attr_value(ind[j + i * 64], 'm');
			d->attr += (d->cnt & (1 << 6)) ? 15 : 0;
			vm_display_node(d, 3 + 4 * j, i + 2, map[j + i * 64]);
			if (d->cnt)
			{
				if ((d->cnt & 63) == 1 && (d->cnt & (1 << 6)))
					d->cnt ^= (1 << 6);
				ind[j + i * 64] = (ind[j + i * 64] & 7) | ((d->cnt - 1) << 3);
			}
		}
	}
}
