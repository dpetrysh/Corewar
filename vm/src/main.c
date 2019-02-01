/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleksiu <soleksiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:33:22 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/12/14 14:18:05 by soleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			vm_sort_champions(t_c *c)
{
	short			i;
	short			j;
	t_ch			*tmp;

	i = -1;
	while (++i < c->ch_count - 2)
	{
		j = -1;
		while (++j < c->ch_count - i - 1)
			if (c->ch[j]->index > c->ch[j + 1]->index)
			{
				tmp = c->ch[j];
				c->ch[j] = c->ch[j + 1];
				c->ch[j + 1] = tmp;
			}
	}
}

static void			vm_print_results(t_c *c)
{
	if (c->fl & C_LLOG || c->fl & C_LOG)
		ft_fprintf(c->log_fd, "Player %d (%s) won.\n", \
			c->ch[c->winner_index]->index, c->ch[c->winner_index]->name);
	else if ((!(c->fl & C_VISUAL) && !(c->fl & C_DEBUG)) ||
		((c->fl & C_DEBUG) && (c->dump_cycles > c->cycles_all)))
	{
		vm_print_champions_list(c);
		ft_printf("Player %d "BOLD"(%s)"NC" won.\n", \
			c->ch[c->winner_index]->index, c->ch[c->winner_index]->name);
	}
}

int					main(int argc, char **argv)
{
	t_c				*c;
	int				i;

	i = -1;
	CHECK1((c = (t_c*)ft_memalloc(sizeof(t_c))));
	vm_parce_fl(c, argc, argv);
	if (!c->ch_count)
		vm_error(c, "No champions.");
	if (c->fl & C_LOG || c->fl & C_LLOG)
		if ((c->log_fd = open("./log.txt", O_RDWR | O_CREAT, S_IRWXU)) < 0)
			vm_error(c, "Bad/miss log file");
	while (++i < c->ch_count)
		vm_parce_champion(c, c->ch[i]);
	vm_sort_champions(c);
	vm_generate_map(c);
	if (c->fl & C_VISUAL || c->fl & C_DEBUG)
		init_ncurs(c);
	vm_game(c);
	vm_print_results(c);
	return (0);
}
