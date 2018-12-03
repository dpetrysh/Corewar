/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:33:13 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/11/07 17:33:15 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include "ft_printf.h"
# include "op.h"
# include <ncurses.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PINK "\033[0;35m"
# define CYAN "\033[0;36m"
# define LGRAY "\033[0;37m"
# define NC "\033[0m"
# define PRED(X) ft_printf(RED "%s" NC,X)
# define PGREEN(X) ft_printf(GREEN "%s" NC,X)
# define PYELLOW(X) ft_printf(YELLOW "%s" NC,X)
# define PBLUE(X) ft_printf(BLUE "%s" NC,X)
# define PPINK(X) ft_printf(PINK "%s" NC,X)
# define PCYAN(X) ft_printf(CYAN "%s" NC,X)

# define C_DEBUG		(1 << 0)
# define C_VISUAL		(1 << 1)
# define C_FLAG_3		(1 << 2)
# define C_FLAG_4		(1 << 3)
# define C_FLAG_5		(1 << 4)

typedef struct		s_ch
{
	int				index;
	char			*file;
	char			*name;
	char			*comment;
	int				code_size;
	unsigned char	*code;
}					t_ch;

typedef struct		s_c
{
	int				fl;
	char			error;
	short			fd;
	short			ch_count;
	t_ch			*ch[MAX_PLAYERS];
	unsigned char	*map;
	unsigned char	*map_index;
	char			*name;
}					t_c;

void				vm_parce_champion(t_c *c, t_ch *ch, char *file);
void				vm_parce_fl(t_c *c, char **argv);

void				vm_generate_map(t_c *c);

void				vm_error(t_c *c, char *str);
void				vm_ch_error(t_c *c, t_ch *ch, char *str);

void				vm_prin_mem(unsigned char *mem, int n);

void				print_in_middle(WINDOW *win, int starty, int startx, int width, char *string);
void				show_map(unsigned char *map);

#endif
