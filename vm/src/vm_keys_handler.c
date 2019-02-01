/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_keys_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleksiu <soleksiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 22:32:49 by soleksiu          #+#    #+#             */
/*   Updated: 2018/12/13 22:32:50 by soleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "limits.h"

static void			vm_keys_we(t_c *data, int key)
{
	float			delta;

	if (key == 'w' && data->vis_delay < VISDELAYMAX)
	{
		delta = (VISDELAYMAX - VISDELAYMIN) / 100;
		data->vis_delay += data->vis_delay < VISDELAYMAX ? delta : 0;
		if (data->vis_delay > VISDELAYMAX)
			data->vis_delay = VISDELAYMAX;
	}
	else if (key == 'e' && data->vis_delay > VISDELAYMIN)
	{
		delta = (VISDELAYMAX - VISDELAYMIN) / 100;
		data->vis_delay -= delta;
		if (data->vis_delay < VISDELAYMIN)
			data->vis_delay = VISDELAYMIN;
	}
}

int					vm_keys_handler(t_c *data)
{
	int				key;

	key = wgetch(data->wnd_ptr);
	if (key == 'q')
	{
		endwin();
		exit(0);
	}
	else if (data->fl & C_DEBUG && key == ' ' && data->game_running)
		data->pause = 0;
	else if (key == 'p' && !(data->fl & C_DEBUG) && data->game_running)
		data->pause = data->pause ? 0 : 1;
	else if (key == 'w' || key == 'e')
		vm_keys_we(data, key);
	return (1);
}
