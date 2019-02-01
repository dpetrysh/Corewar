/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_command_aff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soleksiu <soleksiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 18:05:56 by soleksiu          #+#    #+#             */
/*   Updated: 2018/12/23 18:05:56 by soleksiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				vm_command_aff(t_c *data, t_pc *carriage)
{
	int				reg_nb;
	int				print_val;

	reg_nb = carriage->val[0] - 1;
	print_val = carriage->reg[reg_nb] % 256;
	if (data->fl & C_VISUAL || data->fl & C_DEBUG)
	{
		attron(A_BOLD);
		mvprintw(40, 260, "Aff: %c ", print_val);
		attroff(A_BOLD);
	}
	else
		ft_printf("Aff: %c\n", print_val);
}
