/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_create_extended_logs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleksiu <soleksiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 00:09:40 by soleksiu          #+#    #+#             */
/*   Updated: 2018/12/28 00:09:42 by soleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			ft_printbits(int fd, unsigned char val)
{
	int				i;

	i = 0;
	write(fd, "Bits:   ", 8);
	while (i < 8)
	{
		if (val & (1 << 7))
			write(fd, "1", 1);
		else
			write(fd, "0", 1);
		if (i && ((i + 1) % 2 == 0))
			write(fd, " ", 1);
		val = val << 1;
		i++;
	}
	write(fd, "\n", 1);
}

static void			vm_write_executed_code(t_c *data, t_pc *car, int code_size)
{
	int				i;
	int				start_pos;

	start_pos = car->map_pos;
	i = 0;
	ft_fprintf(data->log_fd, "Code of the command: ");
	while (i < code_size)
	{
		ft_fprintf(data->log_fd, "%02hx%c",
			data->map[start_pos + i], i < code_size - 1 ? ' ' : '\n');
		i++;
	}
}

static char			*vm_get_reg_type(int reg_val)
{
	if (reg_val == REG_CODE)
		return ("T_REG");
	else if (reg_val == IND_CODE)
		return ("T_IND");
	else if (reg_val == DIR_CODE)
		return ("T_DIR");
	return ("NONE");
}

void				vm_create_extended_logs(t_c *data, t_pc *crg, int move)
{
	ft_fprintf(data->log_fd, "Cycle #%d\n", data->cycles_all + 1);
	ft_fprintf(data->log_fd, "Executed command:    %s\n", crg->cur_op->name);
	vm_write_executed_code(data, crg, move);
	if (crg->cur_op->codage)
	{
		ft_fprintf(data->log_fd, "Codage: %x\n", data->map[crg->map_pos + 1]);
		ft_printbits(data->log_fd, data->map[crg->map_pos + 1]);
		ft_fprintf(data->log_fd, "Arguments & their values: \n");
		ft_fprintf(data->log_fd, "	*arg1: %s\t*val1: % 6d(%#02x)\n", \
			vm_get_reg_type(crg->args[0]), crg->val[0], crg->val[0]);
		ft_fprintf(data->log_fd, "	*arg2: %s\t*val2: % 6d(%#02x)\n", \
			vm_get_reg_type(crg->args[1]), crg->val[1], crg->val[1]);
		ft_fprintf(data->log_fd, "	*arg3: %s\t*val3: % 6d(%#02x)\n", \
			vm_get_reg_type(crg->args[2]), crg->val[2], crg->val[2]);
	}
	else
	{
		ft_fprintf(data->log_fd, "No codage for this command\n");
		ft_fprintf(data->log_fd, "Arguments & their values: \n");
		ft_fprintf(data->log_fd, "	*arg1: T_DIR\t*val1: % 6d(%#02x)\n", \
		crg->val[0], crg->val[0]);
	}
	ft_fprintf(data->log_fd, "Command execute in pos: %d\n", MOD(crg->map_pos));
	ft_fprintf(data->log_fd, "Carriage movement: %d\n", move);
	ft_fprintf(data->log_fd, "___________________________________________\n");
}
