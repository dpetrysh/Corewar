/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 16:47:52 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/12/02 16:47:53 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static short		vm_check_cor_file(t_c *c, char *file)
{
	int				len;

	len = ft_strlen(file);
	if (len < 5)
		vm_error(c, "Bad \".cor\" file.");
	if (ft_strequ(file + len - 4, ".cor") == 0)
		vm_error(c, "Bad \".cor\" file.");
	return (1);
}

static void			vm_parce_cor_files(t_c *c, char *file, int index)
{
	short			i;

	i = 1;
	if (c->ch_count >= MAX_PLAYERS)
		vm_error(c, "Too many players.");
	if (!(c->ch[c->ch_count] = (t_ch*)ft_memalloc(sizeof(t_ch))))
		vm_error(c, "Malloc failed.");
	if (index > 0)
		c->ch[c->ch_count]->index = index;
	else
	{
		while (!vm_check_index(c, i))
			i++;
		c->ch[c->ch_count]->index = i;
	}
	c->ch[c->ch_count++]->file = file;
}

static void			vm_parce_n_param(t_c *c, int *i, int ac, char **av)
{
	int				in;
	char			*str;

	if (ac <= *i + 1)
		vm_error(c, "Very few arguments");
	in = ft_atoi(av[++(*i)]);
	str = ft_itoa(in);
	if ((*i < ac) && (in > 0) && (in <= MAX_PLAYERS) && ft_strequ(str, av[*i]))
		if (vm_check_index(c, in))
		{
			(*i)++;
			if ((*i < ac) && vm_check_cor_file(c, av[*i]))
				vm_parce_cor_files(c, av[*i], in);
		}
		else
			vm_error(c, "This index already exist.");
	else
		vm_error(c, "This parameter must be a positive number.");
	free(str);
}

static void			vm_flag_dump(t_c *c, int argc, char **argv, int *i)
{
	char *dump_cycles_str;

	if (((*i)++) + 2 > argc)
		vm_print_help(c);
	c->dump_cycles = ft_atoi(argv[*i]);
	dump_cycles_str = ft_itoa(c->dump_cycles);
	if (!(ft_strequ(dump_cycles_str, argv[*i])) || c->dump_cycles < 0)
		vm_error(c, "Incorrect cycle number for dump.");
	c->fl |= C_DUMP;
	free(dump_cycles_str);
}

void				vm_parce_fl(t_c *c, int argc, char **argv)
{
	int				i;

	i = 0;
	argc <= 1 ? vm_print_help(c) : 0;
	while (++i < argc)
	{
		if (ft_strequ(argv[i], "-h"))
			vm_print_help(c);
		else if (ft_strequ(argv[i], "-v"))
			c->fl |= C_VISUAL;
		else if (ft_strequ(argv[i], "-s"))
			c->fl |= C_SOUND;
		else if (ft_strequ(argv[i], "-d"))
			c->fl |= C_DEBUG;
		else if (ft_strequ(argv[i], "-l") || ft_strequ(argv[i], "-ll"))
			c->fl |= (ft_strequ(argv[i], "-l")) ? C_LOG : C_LLOG;
		else if (ft_strequ(argv[i], "-dump"))
			vm_flag_dump(c, argc, argv, &i);
		else if (ft_strequ(argv[i], "-n"))
			vm_parce_n_param(c, &i, argc, argv);
		else if (vm_check_cor_file(c, argv[i]))
			vm_parce_cor_files(c, argv[i], -1);
		else
			vm_print_help(c);
	}
}
