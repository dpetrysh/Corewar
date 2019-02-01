/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleksiu <soleksiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 15:26:00 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/12/13 15:19:29 by soleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_error(t_c *c, char *str)
{
	c->error = 1;
	ft_fprintf(2, RED "ERROR:" NC);
	ft_fprintf(2, " %s\n", str);
	ft_fprintf(2, "For more information type './corewar -h'\n", str);
	exit(-1);
}

void				vm_ch_error(t_c *c, t_ch *ch, char *str)
{
	c->error = 1;
	ft_fprintf(2, RED "%s:" NC, ch->file);
	ft_fprintf(2, " %s\n", str);
	exit(-1);
}

static char			*vm_pick_player_color(unsigned char map_value)
{
	char *color_modif;

	color_modif = LGRAY;
	if ((map_value & 7) == 0)
		color_modif = LGRAY;
	else if ((map_value & 7) == 1)
		color_modif = GREEN;
	else if ((map_value & 7) == 2)
		color_modif = BLUE;
	else if ((map_value & 7) == 3)
		color_modif = RED;
	else if ((map_value & 7) == 4)
		color_modif = YELLOW;
	return (color_modif);
}

void				vm_print_champions_list(t_c *c)
{
	int				i;
	int				fd;
	char			*player_color;

	i = -1;
	fd = c->fl & C_LOG ? c->log_fd : 0;
	ft_fprintf(fd, "%s\n", c->fl & C_LOG ? "Introducing contestants..." : \
		"Players list:");
	while (++i < c->ch_count)
	{
		if (c->fl & C_LOG)
		{
			ft_fprintf(fd, "* Player %d, weighing %d bytes, \"%s\" ",
				c->ch[i]->index, c->ch[i]->code_size, c->ch[i]->name);
			ft_fprintf(fd, "(\"%s\") !\n", c->ch[i]->comment);
		}
		else
		{
			player_color = vm_pick_player_color(c->ch[i]->index);
			ft_fprintf(fd, "* Player %d aka \"%s%s%s\" ", c->ch[i]->index,
			player_color, c->ch[i]->name, NC);
			ft_fprintf(fd, "(\"%s\") !\n", c->ch[i]->comment);
			ft_fprintf(fd, "    Code size: %d bytes\n", c->ch[i]->code_size);
		}
	}
}

void				vm_print_mem(t_c *c, unsigned char *mem, int n)
{
	int				i;
	char			*color_modif;

	i = -1;
	if (c->fl & C_DUMP)
		vm_print_champions_list(c);
	while (++i < n)
	{
		if (c->fl & C_DUMP && i % 32 == 0)
			ft_printf("0x%04x : ", i);
		color_modif = vm_pick_player_color(c->map_index[i]);
		ft_printf("%s", color_modif);
		ft_printf("%02hhx%c"NC, mem[i], i == 0 || (i + 1) % 32 ? ' ' : '\n');
	}
}
