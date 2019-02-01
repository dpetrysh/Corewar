/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 20:31:33 by vsokolog          #+#    #+#             */
/*   Updated: 2018/12/29 20:31:35 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "op.h"
# include <ncurses.h>

typedef unsigned int	t_uint;
typedef unsigned char	t_uch;

/*
** Process (a.k.a. carriage/caret)
** Fields:
**  - bot_id: index of the carriage
**  - map_pos: carriage position on the map.
**  - start_pos: carriage first placeent position.
**  - carry: flag that is need in zjmp
**  - reg[n]: registry
**  - sleep: cycles to action
**  - alive: count for champions "I'm alive!"
**  - cur_op: current operation being executed
*/

typedef struct			s_pc
{
	int					bot_id;
	unsigned int		map_pos;
	char				carry;
	unsigned int		reg[REG_NUMBER];
	short				sleep;
	int					alive;
	t_op				*cur_op;
	char				args[3];
	int					val[3];
	int					pc_id;
}						t_pc;

/*
** Champions structure
** Fields:
**  - index: id of the champion
**  - file: champion file path
**  - name: champion name
**  - comment: comment fiels
**  - code_size: size of executable code
**  - code: executable code
*/

typedef struct			s_ch
{
	int					index;
	char				*file;
	char				*name;
	char				*comment;
	int					code_size;
	unsigned char		*code;
	int					lives;
	int					last_live;
}						t_ch;

/*
** Main structure
** Fields:
**  - fl: input flags
**  - error: error flag
**  - dump_cycles:
**  - ch_count: number of champions
**  - ch[n]: array of champions
**  - map: circular arena
**  - map_index: map of indexes
**  - carriage_list: list of carriages
**  - wnd_ptr: for visualisation
**  - cycle_to_die: cycles to check for alive champions
**  - cycles_all: cycles for visualisation
**  - cycles_ingame: cycles in one game cycle :)
**  - pause: indicates pause state in visualiser
**  - winner_index
**  - visualiser_delay
**  - ps_alive_nb: live command execution in current cycles_ingame period
**  - checks_nb: number checks live which made after each cycles_ingame period
*/

typedef struct			s_c
{
	int					fl;
	short				log_fd;
	char				error;
	int					dump_cycles;
	short				ch_count;
	t_ch				*ch[MAX_PLAYERS];
	unsigned char		*map;
	short				*map_index;
	t_list				*carriage_list;
	WINDOW				*wnd_ptr;
	int					cycle_to_die;
	int					cycles_all;
	int					cycles_ingame;
	int					key_p;
	int					winner_index;
	char				game_running;
	char				pause;
	char				show_menu;
	int					vis_delay;
	int					ps_alive_nb;
	int					checks_nb;
	int					total_crg_nb;
	int					height;
	char				attr;
	short				cnt;
}						t_c;

#endif
