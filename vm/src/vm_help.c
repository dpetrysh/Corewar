/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 16:44:31 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/12/02 16:44:39 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			vm_logo(t_c *c)
{
	int				fd;
	int				ret;
	char			*line;

	if ((fd = open("./logo.txt", O_RDONLY)) < 0)
		vm_error(c, "Missing logo.txt file");
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_printf(BLUE "%s\n" NC, line);
		free(line);
	}
}

void				vm_print_help(t_c *c)
{
	vm_logo(c);
	PCYAN("usage: ./corewar [OPTION] [-dump NBR_CYCLES] [[-n NUMBER]");
	PCYAN(" CHAMPION.cor] ...\n");
	PBOLD("Your may add the following arguments for: \n");
	PYELLOW("    -s         -> activate sounds\n");
	PYELLOW("    -h         -> print this message\n");
	PYELLOW("    -dump      -> set NBR_CYCLES\n");
	PYELLOW("    -v         -> enable visualization\n");
	PYELLOW("    -d         -> visualization in debugging mode\n");
	PYELLOW("    -l         -> short logging in file \"log.txt\"\n");
	PYELLOW("    -ll        -> extended logging in file \"log.txt\"\n");
	PYELLOW("    -n         -> set INDEX for champion\n");
	exit(0);
}
