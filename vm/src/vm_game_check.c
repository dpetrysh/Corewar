/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_game_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 01:13:56 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/12/28 01:13:58 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			ft_lst_dell_link(t_list **alst, t_list *elem_to_del)
{
	t_list			*lst_pt;
	t_list			*to_dell;

	lst_pt = *alst;
	to_dell = NULL;
	if (!alst || !*alst || !elem_to_del)
		return ;
	if (*alst == elem_to_del)
	{
		*alst = (*alst)->next;
		ft_lstdelone(&elem_to_del, NULL);
		return ;
	}
	while (lst_pt)
	{
		if (lst_pt->next == elem_to_del)
		{
			to_dell = lst_pt->next;
			lst_pt->next = lst_pt->next->next;
			ft_lstdelone(&to_dell, NULL);
		}
		lst_pt = lst_pt->next;
	}
}

static void			vm_check_carriage_alive(t_c *data)
{
	t_list			*lst_pt;
	t_pc			*cur_carriage;

	lst_pt = data->carriage_list;
	while (lst_pt)
	{
		cur_carriage = (t_pc *)lst_pt->content;
		if (cur_carriage->alive == 0)
		{
			ft_lst_dell_link(&data->carriage_list, lst_pt);
			data->total_crg_nb--;
			if (data->fl & C_SOUND && data->fl & C_VISUAL)
				beep();
		}
		else
			cur_carriage->alive = 0;
		lst_pt = lst_pt->next;
	}
}

static void			vm_reset_champions(t_c *data)
{
	int i;

	i = -1;
	while (++i < data->ch_count)
		data->ch[i]->lives = 0;
}

void				vm_check_game_state(t_c *data)
{
	data->checks_nb++;
	vm_check_carriage_alive(data);
	if (data->ps_alive_nb >= NBR_LIVE || data->checks_nb == MAX_CHECKS)
	{
		data->cycle_to_die -= CYCLE_DELTA;
		data->checks_nb = 0;
	}
	if (data->cycle_to_die <= 0 || data->ps_alive_nb == 0)
	{
		data->pause = 1;
		data->game_running = 0;
	}
	data->ps_alive_nb = 0;
	data->cycles_ingame = 0;
	vm_reset_champions(data);
}
