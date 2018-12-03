/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_initial.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 15:37:56 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/11/25 15:37:58 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_generate_map(t_c *c)
{
	int				i;

	c->map = (unsigned char *)ft_memalloc(sizeof(char) * (MEM_SIZE + 1));
	c->map_index = (unsigned char *)ft_memalloc(sizeof(char) * (MEM_SIZE + 1));
	i = -1;
	while (++i < c->ch_count)
	{
		ft_memcpy(c->map + i * (MEM_SIZE / c->ch_count), \
			c->ch[i]->code, c->ch[i]->code_size);
		ft_memset(c->map_index + i * (MEM_SIZE / c->ch_count), \
			c->ch[i]->index , c->ch[i]->code_size);
	}
	vm_prin_mem(c->map, MEM_SIZE);
	show_map(c->map);
	// vm_prin_mem(c->map_index, MEM_SIZE);
}
