/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		str_num_cmp(unsigned char *s, unsigned int num)
{
	return ((unsigned int)(s[3] | s[2] << 8 | s[1] << 16 | s[0] << 24) == num);
}

static void		bot_checker(t_vm *vm, int fd, int i)
{
	unsigned char	a[4];

	if ((fd = open(vm->bot_filenames[i], O_RDONLY)) == -1)
		err_ex("can't open file\n");
	if (read(fd, a, 4) != 4 || str_num_cmp(a, COREWAR_EXEC_MAGIC) == 0)
		err_ex("invalid magic number\n");
	if (read(fd, vm->bot[i].name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		err_ex("not enough info in .cor file\n");
	if (read(fd, a, 4) != 4 || str_num_cmp(a, 0) == 0)
		err_ex("four zeroed bytes after bot name not found\n");
	if (read(fd, a, 4) != 4)
		err_ex("not enough info in .cor file\n");
	if ((vm->bot[i].size = a[3] | a[2] << 8) > CHAMP_MAX_SIZE ||
		vm->bot[i].size == 0 || a[1] > 0 || a[0] > 0)
		err_ex("size of the bot is invalid\n");
	if (read(fd, vm->bot[i].comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		err_ex("not enough info in .cor file\n");
	if (read(fd, a, 4) != 4 || str_num_cmp(a, 0) == 0)
		err_ex("four zeroed bytes after bot comment not found\n");
	if (read(fd, vm->bot[i].bot, vm->bot[i].size) != vm->bot[i].size)
		err_ex("not enough info in .cor file\n");
	if (read(fd, a, 1) != 0)
		err_ex("excess data at the end of the file\n");
	if (close(fd) == -1)
		err_ex("while closing file descriptor\n");
}

void			cor_files_reader(t_vm *vm)
{
	int				i;

	i = -1;
	while (++i < vm->number_of_bots)
		bot_checker(vm, -1, i);
}
