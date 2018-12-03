/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:33:22 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/11/07 17:33:23 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_parce_fl(t_c *c, char **argv)
{
	(void)c;
	(void)argv;
}

int					main(int argc, char **argv)
{
	t_c				*c;
	short			ret;
	int				i;

	CHECK1((c = (t_c*)ft_memalloc(sizeof(t_c))));
	if (argc > 1)
	{
		vm_parce_fl(c, argv);
		c->ch_count = argc - 1;
		i = -1;
		while (++i < argc - 1)
		{
			CHECK1((c->ch[i] = (t_ch*)ft_memalloc(sizeof(t_ch))));
			c->ch[i]->index = i + 1;
			vm_parce_champion(c, c->ch[i], argv[i + 1]);
		}
		vm_generate_map(c);
	}
	(void)ret;
	return (0);
}
