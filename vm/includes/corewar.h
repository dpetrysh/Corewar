/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleksiu <soleksiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:33:13 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/12/13 15:12:19 by soleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <math.h>
# include "ft_printf.h"
# include "structures.h"

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PINK "\033[0;35m"
# define CYAN "\033[0;36m"
# define LGRAY "\033[0;37m"
# define BOLD "\033[1m"
# define NC "\033[0m"
# define PRED(X) ft_printf(RED "%s" NC,X)
# define PGREEN(X) ft_printf(GREEN "%s" NC,X)
# define PYELLOW(X) ft_printf(YELLOW "%s" NC,X)
# define PBLUE(X) ft_printf(BLUE "%s" NC,X)
# define PPINK(X) ft_printf(PINK "%s" NC,X)
# define PCYAN(X) ft_printf(CYAN "%s" NC,X)
# define PBOLD(X) ft_printf(BOLD "%s" NC,X)

# define VISDELAYMIN 10
# define VISDELAYMAX 70000

# define C_DEBUG		(1 << 0)
# define C_VISUAL		(1 << 1)
# define C_LOG			(1 << 2)
# define C_LLOG			(1 << 3)
# define C_FLAG_5		(1 << 4)
# define C_SOUND		(1 << 5)
# define C_DUMP			(1 << 6)

# define MOD(x)			((x) % MEM_SIZE)

void				vm_parce_champion(t_c *c, t_ch *ch);
void				vm_parce_fl(t_c *c, int argc, char **argv);
short				vm_check_index(t_c *c, int n);

void				vm_generate_map(t_c *c);

void				vm_error(t_c *c, char *str);
void				vm_ch_error(t_c *c, t_ch *ch, char *str);

void				vm_print_mem(t_c *c, t_uch *mem, int n);
void				vm_print_help(t_c *c);
void				vm_print_champions_list(t_c	*c);
void				vm_game(t_c	*data);
void				vm_check_game_state(t_c *data);

void				show_map(t_c *data, t_uch *map, short *index);
void				vm_display_carriages(t_c *data);
void				vm_display_speed(t_c *data);
void				vm_show_nodes(t_c *d, t_uch *map, short *index, int height);
void				vm_show_info(t_c *data);
void				init_ncurs(t_c	*data);
int					vm_keys_handler(t_c	*data);
void				vm_make_height(t_c *data);

void				vm_read_codage(t_uch n, char ar[3]);
int					vm_args_validate(t_pc *crg, int *skip);
short				vm_get_args(t_c *c, t_pc *pc);
void				vm_get_dir_no_codage(t_c *data, t_pc *crg);

void				vm_command_sti(t_c *data, t_pc *carriage);
void				vm_command_fork(t_c *data, t_pc *carriage);
void				vm_command_lfork(t_c *data, t_pc *carriage);
void				vm_command_add(t_c *data, t_pc *carriage);
void				vm_command_sub(t_c *data, t_pc *carriage);
void				vm_command_live(t_c *data, t_pc *carriage);
void				vm_command_and(t_c *c, t_pc *pc);
void				vm_command_or(t_c *c, t_pc *pc);
void				vm_command_xor(t_c *c, t_pc *pc);
void				vm_command_zjmp(t_c *data, t_pc *carriage);
void				vm_command_aff(t_c *data, t_pc *carriage);
void				vm_command_ld(t_c *c, t_pc *pc);
void				vm_command_lld(t_c *c, t_pc *pc);
void				vm_command_st(t_c *data, t_pc *crg);
void				vm_command_sti(t_c *data, t_pc *crg);
void				vm_command_ldi(t_c *c, t_pc *pc);
void				vm_command_lldi(t_c *c, t_pc *pc);

void				vm_create_short_logs(t_c *data, t_pc *crg, int move);
void				vm_create_extended_logs(t_c *data, t_pc *crg, int move);

#endif
