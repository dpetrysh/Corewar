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

NAME = corewar
FILENAMES = main \
			ft_leaks \
			show_map_1 \
			show_map_2 \
			show_map \
			vm_args_parce \
			vm_args_validate \
			vm_command_add \
			vm_command_aff \
			vm_command_and \
			vm_command_fork \
			vm_command_ld \
			vm_command_ldi \
			vm_command_lfork \
			vm_command_live \
			vm_command_lld \
			vm_command_lldi \
			vm_command_or \
			vm_command_st \
			vm_command_sti \
			vm_command_sub \
			vm_command_xor \
			vm_command_zjmp \
			vm_create_extended_logs \
			vm_create_short_logs \
			vm_game \
			vm_game_check \
			vm_help \
			vm_initial \
			vm_init_ncurs \
			vm_keys_handler \
			vm_param \
			vm_parce \
			vm_print
HEADERS = corewar structures op
SRCDIR = ./src
HDRDIR = ./includes
ODIR = ./obj
CFILES = $(patsubst %, $(SRCDIR)/%.c, $(FILENAMES))
OFILES = $(patsubst %, $(ODIR)/%.o, $(FILENAMES))
HFILES = $(patsubst %, $(HDRDIR)/%.h, $(HEADERS))
LIBDIR = ./libft
LIBFT = $(LIBDIR)/libft.a
LIBHDRDIR = $(LIBDIR)/includes
FLAGS = -Wall -Wextra -Werror -O3

RED = '\033[0;31m'
GR = '\033[0;32m'
NC = '\033[0m'

all: $(NAME)

$(NAME): $(ODIR) $(HFILES) $(OFILES) $(LIBFT)
	@gcc $(FLAGS) $(OFILES) $(LIBFT) -o $(NAME) -lncurses
	@echo ${GR}"================= $(NAME) is up to date. ================="${NC}

$(ODIR)/%.o: $(SRCDIR)/%.c $(HFILES) $(LIBFT)
	@gcc $(FLAGS) -o $@ -c $< -I$(HDRDIR) -I$(LIBHDRDIR)

$(ODIR):
	@mkdir -p $(ODIR)

$(LIBFT):
	@make -C $(LIBDIR) || true

norm:
	@echo ${RED}[Checking the $(NAME) NORM]${NC}
	@norminette $(CFILES) $(HFILES)

fnorm: norm
	@make norm -C ./libft

echo:
	@echo $(HFILES)
	@echo $(HEADERS)
	@echo $(HDRDIR)

clean:
	@rm -Rf $(ODIR)
	@make clean -C $(LIBDIR)

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C $(LIBDIR)

test: all
	./corewar -v forktest.cor

re: fclean all
