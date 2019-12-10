/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		writenumfd(int fd, unsigned int num)
{
	if (num > 9)
		writenumfd(fd, num / 10);
	num = num % 10 + '0';
	write(fd, &num, 1);
}

static int		arg_out(int fd, unsigned char *k, int t, int n)
{
	if (t == T_REG)
	{
		write(fd, "r", 1);
		if (*k > 99)
			err_ex("Error: register number is too large\n");
		writenumfd(fd, *k);
		return (1);
	}
	else if (t == T_DIR)
	{
		write(fd, "%", 1);
		if (n == 1)
			writenumfd(fd, k[1] | *k << 8);
		else if (n == 0)
			writenumfd(fd, k[3] | k[2] << 8 | k[1] << 16 | *k << 24);
		return (n == 1 ? 2 : 4);
	}
	if (*k > 9)
		writenumfd(fd, 0xffff - (k[1] | *k << 8));
	else
		writenumfd(fd, k[1] | *k << 8);
	return (2);
}

static int		take_arg2(int t, int c)
{
	if (t == (T_REG | T_IND))
	{
		if (c == REG_CODE)
			return (T_REG);
		else if (c == IND_CODE)
			return (T_IND);
		err_ex("Error: wrong argument\n");
	}
	else if (t == (T_DIR | T_IND))
	{
		if (c == DIR_CODE)
			return (T_DIR);
		else if (c == IND_CODE)
			return (T_IND);
		err_ex("Error: wrong argument\n");
	}
	err_ex("Error: wrong argument\n");
	return (0);
}

static int		take_arg(int t, int c)
{
	if ((t == T_REG || t == T_DIR || t == T_IND) && c == 0)
		return (t);
	if ((t == T_REG && c == REG_CODE) || (t == T_DIR && c == DIR_CODE) ||
		(t == T_IND && c == IND_CODE))
		return (t);
	else if (t == (T_REG | T_DIR | T_IND))
	{
		if (c == REG_CODE)
			return (T_REG);
		else if (c == DIR_CODE)
			return (T_DIR);
		else if (c == IND_CODE)
			return (T_IND);
		err_ex("Error: wrong argument\n");
	}
	else if (t == (T_REG | T_DIR))
	{
		if (c == REG_CODE)
			return (T_REG);
		else if (c == DIR_CODE)
			return (T_DIR);
		err_ex("Error: wrong argument\n");
	}
	return (take_arg2(t, c));
}

int				arg_output(int fd, int i, t_back *rever)
{
	int		n;
	int		j;
	int		arg;
	int		t_rdi;

	if ((n = rever->code[i++] - 1) > 15)
		err_ex("Error: wrong opcode\n");
	arg = g_op_tab[n].codage == 0 ? 0 : rever->code[i++];
	write(fd, g_op_tab[n].name, str_len(g_op_tab[n].name));
	str_len(g_op_tab[n].name) > 3 ? write(fd, "\t", 1) : write(fd, "\t\t", 2);
	j = 0;
	while (++j <= g_op_tab[n].args_num)
	{
		t_rdi = take_arg(g_op_tab[n].args[j - 1], arg >> (8 - j * 2) & 0x3);
		i += arg_out(fd, rever->code + i, t_rdi, g_op_tab[n].label_size);
		j == g_op_tab[n].args_num ? write(fd, "\n", 1) : write(fd, ", ", 2);
	}
	return (i);
}
