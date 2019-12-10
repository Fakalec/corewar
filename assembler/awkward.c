/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backward.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		make_s(char *f)
{
	int i;
	int fd;

	i = str_len(f) - 2;
	f[i] = '\0';
	f[i - 1] = 's';
	if ((fd = open(f, O_CREAT | O_EXCL | O_WRONLY, 0600)) == -1)
		err_ex("Error: can't create f\n");
	return (fd);
}

static void		s_output(int fd, t_back *back)
{
	unsigned int	i;

	write(fd, ".name	\"", 7);
	write(fd, back->name, str_len(back->name));
	write(fd, "\"\n", 2);
	write(fd, ".comment	\"", 10);
	write(fd, back->comment, str_len(back->comment));
	write(fd, "\"\n\n", 3);
	i = 0;
	while (i < back->size)
		i = arg_output(fd, i, back);
	write(1, "Writing output program to .s f\n", 34);
}

static int		str_cmp1(unsigned char *s, unsigned int n)
{
	return ((unsigned int)(s[3] | s[2] << 8 | s[1] << 16 | s[0] << 24) == n);
}

static void		val_take_cod(int fd, t_back *back)
{
	unsigned char	a[4];

	back->size = 0;
	if (read(fd, a, 4) != 4 || str_cmp1(a, COREWAR_EXEC_MAGIC) == 0)
		err_ex("invalid magic number\n");
	if (read(fd, back->name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		err_ex("not enough info in .cor f\n");
	if (read(fd, a, 4) != 4 || str_cmp1(a, 0) == 0)
		err_ex("four zeroed bytes after bot name not found\n");
	if (read(fd, a, 4) != 4)
		err_ex("not enough info in .cor f\n");
	if ((back->size = a[3] | a[2] << 8 | a[1] << 16 | a[0] << 24) > 2048)
		err_ex("size of the bot is too large\n");
	if (read(fd, back->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		err_ex("not enough info in .cor f\n");
	if (read(fd, a, 4) != 4 || str_cmp1(a, 0) == 0)
		err_ex("four zeroed bytes after bot comment not found\n");
	if (read(fd, back->code, back->size) != back->size)
		err_ex("not enough info in .cor f\n");
	if (read(fd, a, 1) != 0)
		err_ex("excess data at the end of the f\n");
	if (close(fd) == -1)
		err_ex("Error while closing f descriptor\n");
}

void			backward(char *f)
{
	int				fd;
	int				i;
	t_back			back;

	i = str_len(f) - 1;
	if (i < 4 || f[i - 3] != '.' || f[i - 2] != 'c' ||
		f[i - 1] != 'o' || f[i] != 'r')
	{
		write(2, "Error f should have .cor extension\n", 38);
		return ;
	}
	if ((fd = open(f, O_RDONLY)) == -1 || (read(fd, &i, 0)) == -1)
	{
		write(2, "Error f does not exist\n", 26);
		return ;
	}
	val_take_cod(fd, &back);
	fd = make_s(f);
	s_output(fd, &back);
}
