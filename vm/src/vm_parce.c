/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parce.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtsyvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 15:25:32 by dtsyvin           #+#    #+#             */
/*   Updated: 2018/11/25 15:25:35 by dtsyvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

short				vm_check_index(t_c *c, int n)
{
	short			i;

	i = -1;
	while (++i < c->ch_count)
		if (n == c->ch[i]->index)
			return (0);
	return (1);
}

static void			vm_check_magic(t_c *c, t_ch *ch, int fd)
{
	int				ret;
	unsigned char	*buf;

	buf = (unsigned char *)ft_memalloc(sizeof(char) * 4);
	if ((ret = read(fd, buf, 4) < 4))
		vm_ch_error(c, ch, "Bad magic header.");
	if (buf[3] + (buf[2] << 8) + (buf[1] << 16) + (buf[0] << 24) \
			!= COREWAR_EXEC_MAGIC)
		vm_ch_error(c, ch, "Bad magic header.");
	free(buf);
}

static void			vm_check_zero(t_c *c, t_ch *ch, int fd)
{
	int				ret;
	char			*buf;

	buf = (char *)ft_memalloc(sizeof(char) * 4);
	if ((ret = read(fd, buf, 4) < 4))
		vm_ch_error(c, ch, "Bad champion name end.");
	if ((*(int *)buf))
		vm_ch_error(c, ch, "Bad champion name end.");
	free(buf);
}

static void			vm_parce_ch_size(t_c *c, t_ch *ch, int fd)
{
	int				ret;
	unsigned char	*buf;

	buf = (unsigned char *)ft_memalloc(sizeof(char) * 4);
	if ((ret = read(fd, buf, 4) < 4))
		vm_ch_error(c, ch, "Bad champion size.");
	ch->code_size = buf[3] + (buf[2] << 8) + (buf[1] << 16) + (buf[0] << 24);
	free(buf);
}

void				vm_parce_champion(t_c *c, t_ch *ch)
{
	short			fd;
	int				ret;
	char			tmp[1];

	if ((fd = open(ch->file, O_RDONLY)) < 0)
		vm_error(c, "Bad file");
	vm_check_magic(c, ch, fd);
	ch->name = (char *)ft_memalloc(sizeof(char) * (PROG_NAME_LENGTH + 1));
	if ((ret = read(fd, ch->name, PROG_NAME_LENGTH)) < PROG_NAME_LENGTH || \
		ft_strequ(ch->name, ""))
		vm_ch_error(c, ch, "Bad champion name.");
	vm_check_zero(c, ch, fd);
	vm_parce_ch_size(c, ch, fd);
	ch->comment = (char *)ft_memalloc(sizeof(char) * (COMMENT_LENGTH + 1));
	if ((ret = read(fd, ch->comment, COMMENT_LENGTH)) < COMMENT_LENGTH || \
		ft_strequ(ch->comment, ""))
		vm_ch_error(c, ch, "Bad champion comment.");
	vm_check_zero(c, ch, fd);
	ch->code = (unsigned char*)ft_memalloc(sizeof(char) * (CHAMP_MAX_SIZE + 1));
	if ((ret = read(fd, ch->code, CHAMP_MAX_SIZE)) < 0 || \
		ft_strequ((char*)ch->code, ""))
		vm_ch_error(c, ch, "Bad champion code.");
	if (ret != ch->code_size || (ret = read(fd, tmp, 1)) > 0)
		vm_ch_error(c, ch, "Bad champion code.");
	close(fd);
}
