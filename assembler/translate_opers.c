/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_opers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		ignore_arg(char *f, int *i)
{
	while (f[*i] != '\n' && f[*i] != SEPARATOR_CHAR)
		*i += 1;
	if (f[*i] != SEPARATOR_CHAR)
		close_lex(f, *i);
	*i += 1;
	while (f[*i] == ' ' || f[*i] == '\t')
		*i += 1;
}

static int		take_arg3(int n, int arg, int i, t_asm *as)
{
	if (arg == (T_DIR | T_IND))
	{
		if (check_norm(as->f, i))
			return (take_norm_val(i + 1, as));
		else if (check_wrong(as->f, i))
			return (take_wrong_val(i, as));
		else if (check_regis(as->f, i))
			close_wrong_par(n, T_DIR | T_IND, i, as);
	}
	else if (arg == (T_REG | T_DIR | T_IND))
	{
		if (check_regis(as->f, i))
			return (take_reg_val(i + 1, as));
		else if (check_norm(as->f, i))
			return (take_norm_val(i + 1, as));
		else if (check_wrong(as->f, i))
			return (take_wrong_val(i, as));
	}
	close_lex(as->f, i);
	return (0);
}

static int		take_arg2(int n, int arg, int i, t_asm *as)
{
	if (arg == (T_REG | T_DIR))
	{
		if (check_regis(as->f, i))
			return (take_reg_val(i + 1, as));
		else if (check_norm(as->f, i))
			return (take_norm_val(i + 1, as));
		else if (check_wrong(as->f, i))
			close_wrong_par(n, T_REG | T_DIR, i, as);
	}
	else if (arg == (T_REG | T_IND))
	{
		if (check_regis(as->f, i))
			return (take_reg_val(i + 1, as));
		else if (check_wrong(as->f, i))
			return (take_wrong_val(i, as));
		else if (check_norm(as->f, i))
			close_wrong_par(n, T_REG | T_IND, i, as);
	}
	return (take_arg3(n, arg, i, as));
}

static int		take_arg(int n, int arg, int i, t_asm *as)
{
	if (arg == T_REG)
	{
		if (check_regis(as->f, i))
			return (take_reg_val(i + 1, as));
		else if (check_norm(as->f, i) || check_wrong(as->f, i))
			close_wrong_par(n, T_REG, i, as);
	}
	else if (arg == T_DIR)
	{
		if (check_norm(as->f, i))
			return (take_norm_val(i + 1, as));
		else if (check_regis(as->f, i) || check_wrong(as->f, i))
			close_wrong_par(n, T_DIR, i, as);
	}
	else if (arg == T_IND)
	{
		if (check_wrong(as->f, i))
			return (take_wrong_val(i, as));
		else if (check_regis(as->f, i) || check_norm(as->f, i))
			close_wrong_par(n, T_IND, i, as);
	}
	return (take_arg2(n, arg, i, as));
}

void			translate_opers(int i, int oper_code, t_asm *as)
{
	int n;
	int j;

	if (as->size > BOT_SIZE - 11)
		err_ex("Error: champion size is to large\n");
	as->code[as->size++] = oper_code--;
	as->arg_flag = as->size;
	if (g_op_tab[oper_code].codage == 1)
		as->size++;
	while (as->f[i] != ' ' && as->f[i] != '\t' && as->f[i] != DIRECT_CHAR)
		i++;
	while (as->f[i] == ' ' || as->f[i] == '\t')
		i++;
	j = 0;
	as->code[as->arg_flag] = 0;
	while (++j <= g_op_tab[oper_code].args_num)
	{
		as->t_dir_size = (g_op_tab[oper_code].label_size == 1 ? 2 : 4);
		n = take_arg(j, g_op_tab[oper_code].args[j - 1], i, as) << (8 - j * 2);
		if (g_op_tab[oper_code].codage == 1)
			as->code[as->arg_flag] += n;
		if (j < g_op_tab[oper_code].args_num)
			ignore_arg(as->f, &i);
	}
	validate_argument(as->f, i);
}
