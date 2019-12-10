/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				input_file(char *f, t_asm *as)
{
	int		size;
	int		fd;

	if ((fd = open(f, O_RDONLY)) == -1)
		err_ex("Error: can't read source file\n");
	if (str_len(NAME_CMD_STRING) == 0 || str_len(COMMENT_CMD_STRING) == 0)
		err_ex("Error: empty CMD_STRING\n");
	size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	as->f = (char *)malloc(size + 1);
	read(fd, as->f, size);
	as->f[size] = '\0';
	close(fd);
}

void				make_dot_cor(char *f, t_asm *as)
{
	const char	cor[] = ".cor";
	int			l;
	int			n;

	l = str_len(f);
	n = l - 1;
	while (n >= 0 && f[n] != '.')
		n--;
	if (n < 0)
		n = l;
	as->cor_f_name = (char *)malloc(n + 5);
	l = -1;
	while (++l < n)
		as->cor_f_name[l] = f[l];
	l = 0;
	while (cor[l])
		as->cor_f_name[n++] = cor[l++];
	as->cor_f_name[n] = '\0';
	as->cor_fd = open(as->cor_f_name, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (as->cor_fd == -1)
		err_ex("Error: can't create file\n");
}

static unsigned int	rev_32(unsigned int n)
{
	return ((n & 0xff000000) >> 24) | ((n & 0x00ff0000) >> 8)
	| ((n & 0x0000ff00) << 8) | (n << 24);
}

void				output_dot_cor(t_asm *as)
{
	const unsigned char	zero = 0;
	const unsigned int	magic = rev_32(COREWAR_EXEC_MAGIC);
	const unsigned int	size = rev_32(as->size);
	int					i;

	write(1, "Writing output program to ", 26);
	write(1, as->cor_f_name, str_len(as->cor_f_name));
	write(1, "\n", 1);
	write(as->cor_fd, &magic, 4);
	i = 0;
	while (as->name[i])
		write(as->cor_fd, &as->name[i++], 1);
	while (i++ < PROG_NAME_LENGTH + 4)
		write(as->cor_fd, &zero, 1);
	write(as->cor_fd, &size, 4);
	i = 0;
	while (as->comment[i])
		write(as->cor_fd, &as->comment[i++], 1);
	while (i++ < COMMENT_LENGTH + 4)
		write(as->cor_fd, &zero, 1);
	i = 0;
	while (i < as->size)
		write(as->cor_fd, &as->code[i++], 1);
	close(as->cor_fd);
}

int					main(int ac, char **av)
{
	t_asm	as;

	if (ac == 2)
	{
		init_struct(&as);
		input_file(av[1], &as);
		if (val_translate(&as))
			err_ex("Error: bad source file\n");
		make_dot_cor(av[1], &as);
		output_dot_cor(&as);
		free_every(&as);
	}
	else if (ac == 3 && str_cmp(av[1], "-d"))
		remake_package(av[2], &as);
	else if (ac == 3 && str_cmp(av[1], "-r"))
		backward(av[2]);
	else
		write(1, "usage: ./asm file | -d dir_name | -r file.cor\n", 46);
	return (0);
}
