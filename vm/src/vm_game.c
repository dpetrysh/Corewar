/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleksiu <soleksiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 12:32:46 by soleksiu          #+#    #+#             */
/*   Updated: 2018/12/13 17:34:06 by soleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	vm_run_command(t_c *data, t_pc *car, void (*ft_arr[17])\
	(t_c *d, t_pc *c), int op_code)
{
	int				bytes_to_skip;

	vm_read_codage(data->map[MOD(car->map_pos + 1)], car->args);
	if (vm_args_validate(car, &bytes_to_skip) && vm_get_args(data, car))
	{
		if ((data->fl & C_LOG))
			vm_create_short_logs(data, car, bytes_to_skip);
		else if ((data->fl & C_LLOG))
			vm_create_extended_logs(data, car, bytes_to_skip);
		ft_arr[op_code](data, car);
	}
	if (car->cur_op->op != 9)
		car->map_pos += bytes_to_skip;
	car->sleep = 0;
	ft_bzero(car->args, sizeof(char) * 3);
	ft_bzero(car->val, sizeof(unsigned int) * 3);
}

static void	vm_execute_commands(t_c *data, void (*ft_arr[17])(t_c *d, t_pc *c))
{
	int				op_code;
	t_list			*carriage_lst;
	t_pc			*cur_carriage;

	carriage_lst = data->carriage_list;
	while (carriage_lst)
	{
		cur_carriage = (t_pc *)carriage_lst->content;
		op_code = data->map[cur_carriage->map_pos];
		if (op_code < 1 || op_code > 16)
			cur_carriage->map_pos++;
		else
		{
			cur_carriage->cur_op = ((t_op *)&g_op_tab[op_code - 1]);
			if (cur_carriage->sleep < cur_carriage->cur_op->cycles - 1)
				cur_carriage->sleep++;
			else
				vm_run_command(data, cur_carriage, ft_arr, op_code);
		}
		cur_carriage->map_pos %= MEM_SIZE;
		carriage_lst = carriage_lst->next;
	}
}

static void	vm_create_carriages(t_c *data)
{
	int				i;
	int				carriage_pos;
	t_pc			*cur_carriage;

	i = -1;
	while (++i < data->ch_count)
	{
		data->total_crg_nb++;
		carriage_pos = (i * (MEM_SIZE / data->ch_count));
		cur_carriage = (t_pc *)ft_memalloc(sizeof(t_pc));
		cur_carriage->map_pos = carriage_pos;
		cur_carriage->pc_id = data->total_crg_nb;
		cur_carriage->bot_id = data->ch[i]->index;
		cur_carriage->carry = 0;
		cur_carriage->reg[0] = -1 * cur_carriage->bot_id;
		ft_lstadd(&data->carriage_list, ft_lstnew(cur_carriage, sizeof(t_pc)));
		free(cur_carriage);
	}
}

static void	vm_init_ft_point(void (*ft_arr[17])(t_c *data, t_pc *car))
{
	ft_arr[1] = vm_command_live;
	ft_arr[2] = vm_command_ld;
	ft_arr[3] = vm_command_st;
	ft_arr[4] = vm_command_add;
	ft_arr[5] = vm_command_sub;
	ft_arr[6] = vm_command_and;
	ft_arr[7] = vm_command_or;
	ft_arr[8] = vm_command_xor;
	ft_arr[9] = vm_command_zjmp;
	ft_arr[10] = vm_command_ldi;
	ft_arr[11] = vm_command_sti;
	ft_arr[12] = vm_command_fork;
	ft_arr[13] = vm_command_lld;
	ft_arr[14] = vm_command_lldi;
	ft_arr[15] = vm_command_lfork;
	ft_arr[16] = vm_command_aff;
}

void		vm_game(t_c *data)
{
	void			(*ft_arr[17])(t_c *data, t_pc *carriage);

	data->game_running = 1;
	data->winner_index = data->ch_count - 1;
	data->cycle_to_die = CYCLE_TO_DIE;
	vm_init_ft_point(ft_arr);
	vm_create_carriages(data);
	if ((data->fl & C_VISUAL || data->fl & C_DEBUG) && (data->pause = 1))
		show_map(data, data->map, data->map_index);
	while (data->game_running)
	{
		vm_execute_commands(data, ft_arr);
		if (data->fl & C_DUMP && data->dump_cycles == data->cycles_all)
		{
			ft_printf("Dump of data in cycle #%d\n", data->dump_cycles);
			vm_print_mem(data, data->map, MEM_SIZE);
			exit(0);
		}
		data->cycles_all++;
		data->cycles_ingame++;
		if (data->cycles_ingame == data->cycle_to_die)
			vm_check_game_state(data);
		if (data->fl & C_VISUAL || data->fl & C_DEBUG)
			show_map(data, data->map, data->map_index);
	}
}
