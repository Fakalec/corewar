/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalidates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		write_err_num(unsigned int n)
{
	if (n > 9)
		write_err_num(n / 10);
	n = n % 10 + 48;
	write(2, &n, 1);
}

static int		take_line_num(char *f, int i)
{
	int n;
	int j;

	j = 1;
	n = 0;
	while (n < i)
	{
		if (f[n++] == '\n')
			j++;
	}
	return (j);
}

void			*close_lex(char *f, int n)
{
	int j;
	int i;

	write(2, "Error at line: ", 15);
	write_err_num(take_line_num(f, n));
	write(2, " column: ", 9);
	i = n;
	while (f[i] && f[++i] != '\n')
	{
		if (f[i] == ' ' || f[i] == '\t')
		{
			while (f[i] == ' ' || f[i] == '\t')
				i++;
			f[i] = COMMENT_CHAR;
			if (check_regis(f, n) || check_norm(f, n) || check_wrong(f, n))
				n = i;
		}
	}
	j = 1;
	while (--n >= 0 && f[n] != '\n')
		j++;
	write_err_num(j);
	write(2, "\n", 1);
	exit(1);
}

static void		write_operation_err(int i, char *f)
{
	while (i > 0 && f[i - 1] != '\n')
	{
		if (f[i] == LABEL_CHAR && check_char(f[i - 1]))
		{
			i++;
			while (f[i] == ' ' || f[i] == '\t')
				i++;
			break ;
		}
		i--;
	}
	while (f[i] == ' ' || f[i] == '\t')
		i++;
	while (f[i] != ' ' && f[i] != '\t' && f[i] != DIRECT_CHAR)
		write(2, &f[i++], 1);
}

void			close_wrong_par(int n, int par, int i, t_asm *s)
{
	if (n == 1)
		write(2, "first", 5);
	else if (n == 2)
		write(2, "second", 6);
	else if (n == 3)
		write(2, "thrird", 6);
	write(2, " par type of opcode ", 26);
	write_operation_err(i, s->f);
	write(2, " on line ", 9);
	write_err_num(take_line_num(s->f, i));
	write(2, " must be ", 9);
	if (par == T_REG)
		write(2, "T_REG\n", 6);
	else if (par == T_DIR)
		write(2, "T_DIR\n", 6);
	else if (par == T_IND)
		write(2, "T_IND\n", 6);
	else if (par == (T_REG | T_DIR))
		write(2, "T_REG or T_DIR\n", 15);
	else if (par == (T_REG | T_IND))
		write(2, "T_REG or T_IND\n", 15);
	else if (par == (T_DIR | T_IND))
		write(2, "T_DIR or T_IND\n", 15);
	exit(1);
}
