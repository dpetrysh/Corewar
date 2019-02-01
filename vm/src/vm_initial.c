/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_initial.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleksiu <soleksiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 15:37:56 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/12/13 15:12:46 by soleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			*ft_setcolormap(void *b, int c, size_t len)
{
	while (len > 0)
	{
		((short*)b)[len - 1] = (unsigned short)c;
		len--;
	}
	return (b);
}

void				vm_generate_map(t_c *c)
{
	int		i;
	short	color_code;

	if (c->fl & C_VISUAL || c->fl & C_DEBUG)
	{
		if (MEM_SIZE < 64 || MEM_SIZE > 4 * 1216)
			vm_error(c, "Incorrect MEM_SIZE.");
	}
	else if (MEM_SIZE > 4294967295)
		vm_error(c, "Incorrect MEM_SIZE.");
	c->map = (unsigned char *)ft_memalloc(sizeof(char) * (MEM_SIZE + 1));
	c->map_index = (short*)ft_memalloc(sizeof(short) * (MEM_SIZE + 1));
	i = -1;
	while (++i < c->ch_count)
	{
		color_code = 0;
		ft_memcpy(c->map + i * (MEM_SIZE / c->ch_count), \
		c->ch[i]->code, c->ch[i]->code_size);
		color_code = c->ch[i]->index | color_code;
		ft_setcolormap(c->map_index + i * (MEM_SIZE / c->ch_count), \
		color_code, c->ch[i]->code_size);
	}
}
