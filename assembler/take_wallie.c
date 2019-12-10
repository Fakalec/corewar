/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_vals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static long		ft_atoi(char *str, int i)
{
	int		num;
	int		s;
	int		n;

	s = (str[i] == '-' && ++i) ? -1 : 1;
	while (str[i] == '0')
		i++;
	num = 0;
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i++] - 48;
		n++;
	}
	if (n >= 20)
		return (s == -1 ? 0 : 9223372036854775807);
	return (num * s);
}

static t_list	*take_operat_name(int i, int name_len, t_asm *as)
{
	int		n;
	int		t;
	t_list	*op_label;

	n = 0;
	while (check_char(as->f[i]) == 1)
	{
		i++;
		n++;
	}
	if (n == 0)
		close_lex(as->f, i);
	op_label = (t_list *)malloc(sizeof(t_list));
	op_label->next = as->op_labels;
	op_label->n = as->arg_flag - 1;
	op_label->p = as->size;
	op_label->name_len = name_len;
	op_label->str = (char *)malloc(n + 1);
	op_label->str[n] = '\0';
	i -= n;
	t = -1;
	while (++t < n)
		op_label->str[t] = as->f[i++];
	return (op_label);
}

int				take_reg_val(int i, t_asm *as)
{
	as->code[as->size] = as->f[i] - 48;
	if (as->f[i + 1] >= '0' && as->f[i + 1] <= '9')
		as->code[as->size] = as->code[as->size] * 10 + as->f[i + 1] - 48;
	as->size += 1;
	return (REG_CODE);
}

int				take_norm_val(int i, t_asm *as)
{
	if (as->f[i] == LABEL_CHAR && ++i)
	{
		as->op_labels = take_operat_name(i, as->t_dir_size, as);
		as->size += as->t_dir_size;
	}
	else if (as->t_dir_size == 4)
		as->size += ui_cod(ft_atoi(as->f, i), as->size, as);
	else if (as->t_dir_size == 2)
		as->size += us_cod(ft_atoi(as->f, i), as->size, as);
	return (DIR_CODE);
}

int				take_wrong_val(int i, t_asm *as)
{
	if (as->f[i] == LABEL_CHAR && ++i)
	{
		as->op_labels = take_operat_name(i, 2, as);
		as->size += 2;
	}
	else
		as->size += us_cod(ft_atoi(as->f, i), as->size, as);
	return (IND_CODE);
}
