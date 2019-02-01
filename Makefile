# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtsyvin <dtsyvin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/07 16:11:31 by dtsyvin           #+#    #+#              #
#    Updated: 2018/11/07 16:46:23 by dtsyvin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_1 = asm
NAME_2 = corewar

ASM_DIR = ./asm_dir
VM_DIR = ./vm

all:
	@make -C $(ASM_DIR)
	@cp $(ASM_DIR)/$(NAME_1) .
	@make -C $(VM_DIR)
	@cp $(VM_DIR)/$(NAME_2) .

norm:
	@make norm -C $(ASM_DIR)
	@make norm -C $(VM_DIR)

fnorm:
	@make fnorm -C $(ASM_DIR)
	@make fnorm -C $(VM_DIR)

clean:
	@make clean -C $(ASM_DIR)
	@make clean -C $(VM_DIR)

fclean: clean
	@make fclean -C $(ASM_DIR)
	@make fclean -C $(VM_DIR)
	@/bin/rm -f $(NAME_1)
	@/bin/rm -f $(NAME_2)

re: fclean all
