/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 15:26:00 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/11/25 15:26:09 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_error(t_c *c, char *str)
{
	c->error = 1;
	if (c->fl & C_DEBUG)
		ft_fprintf(2, CYAN "Some debug functions.\n" NC);
	ft_fprintf(2, RED "ERROR:" NC);
	ft_fprintf(2, " %s\n", str);
	exit(-1);
}

void				vm_ch_error(t_c *c, t_ch *ch, char *str)
{
	c->error = 1;
	if (c->fl & C_DEBUG)
		ft_fprintf(2, CYAN "Some debug functions.\n" NC);
	ft_fprintf(2, RED "%s:" NC, ch->file);
	ft_fprintf(2, " %s\n", str);
	exit(-1);
}

void				vm_print_champion(void)
{
	
}

void				vm_prin_mem(unsigned char *mem, int n)
{
	int				i;

	i = -1;
	while (++i < n)
		ft_printf("%02hhx ", mem[i]);
	ft_putchar('\n');
}
