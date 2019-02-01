/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_create_short_logs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleksiu <soleksiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 12:19:23 by soleksiu          #+#    #+#             */
/*   Updated: 2018/12/26 12:19:24 by soleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	vm_output_and_or_xor(t_c *data, t_pc *cr, int move)
{
	if (cr->args[0])
	{
		if (cr->args[0] == IND_CODE)
			ft_fprintf(data->log_fd, "%d", cr->val[0] - move);
		else if (cr->args[0] == REG_CODE)
			ft_fprintf(data->log_fd, "%d",
			(short)cr->reg[cr->val[0] - 1]);
		else
			ft_fprintf(data->log_fd, "%d", cr->val[0]);
		if (cr->args[1])
			ft_fprintf(data->log_fd, " ");
	}
	if (cr->args[1])
	{
		if (cr->args[1] == IND_CODE)
			ft_fprintf(data->log_fd, "%d", cr->val[1] - move);
		else if (cr->args[1] == REG_CODE)
			ft_fprintf(data->log_fd, "%d", (short)cr->reg[cr->val[1] - 1]);
		else
			ft_fprintf(data->log_fd, "%d", cr->val[1]);
		if (cr->args[2])
			ft_fprintf(data->log_fd, " ");
	}
	if (cr->args[2])
		ft_fprintf(data->log_fd, "r%hd", cr->val[2]);
}

static void	vm_output_and_no_codage(t_c *data, t_pc *cr)
{
	ft_fprintf(data->log_fd, "%hd", cr->val[0]);
	if (cr->cur_op->carry)
	{
		if (cr->cur_op->op == 12)
			ft_fprintf(data->log_fd, " (%d)",
				(cr->val[0] % IDX_MOD) + cr->map_pos);
		else if (cr->cur_op->op == 15)
			ft_fprintf(data->log_fd, " (%d)", (cr->val[0]) + cr->map_pos);
		else
			ft_fprintf(data->log_fd, " %s", cr->carry ? "OK" : "FAILED");
	}
}

static void	vm_print_args(t_c *data, t_pc *cr, int move)
{
	int i;

	i = -1;
	if (!cr->cur_op->codage)
		vm_output_and_no_codage(data, cr);
	else if (cr->cur_op->op == 6 || cr->cur_op->op == 7 || cr->cur_op->op == 8)
		vm_output_and_or_xor(data, cr, move);
	else
	{
		while (++i < 3)
		{
			if (cr->args[i])
			{
				if (cr->args[i] == REG_CODE &&
					(cr->val[i] > 0 && cr->val[i] < 17))
					ft_fprintf(data->log_fd, "r");
				ft_fprintf(data->log_fd, "%hd", cr->val[i]);
				if (i + 1 < 3 && cr->args[i + 1])
					ft_fprintf(data->log_fd, " ");
			}
		}
	}
}

void		vm_create_short_logs(t_c *data, t_pc *crg, int move)
{
	static int	frst_outpt = 0;

	frst_outpt == 0 && (frst_outpt = 1) ? vm_print_champions_list(data) : 0;
	if (crg->cur_op->op == 16)
		return ;
	ft_fprintf(data->log_fd, "P%5d | %s ", crg->pc_id, crg->cur_op->name);
	vm_print_args(data, crg, move);
	ft_fprintf(data->log_fd, "\n");
	if (crg->cur_op->op == 11)
	{
		ft_fprintf(data->log_fd, "       | -> store to ",
			crg->bot_id, crg->cur_op->name);
		ft_fprintf(data->log_fd, "%d + %d = %d ", crg->val[1],
			crg->val[2], crg->val[1] + crg->val[2]);
		ft_fprintf(data->log_fd, "(with pc and mod %d)\n",
			crg->map_pos + ((crg->val[1] + crg->val[2]) % IDX_MOD));
	}
}
