/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_operat_and_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		be_oper(const char *a, char *b)
{
	while (*a && *b && *a == *b)
	{
		a++;
		b++;
	}
	return (*a == '\0' && (*b == ' ' || *b == '\t' || *b == DIRECT_CHAR));
}

static int		take_oper(char *f)
{
	int			n;

	n = 0;
	while (g_op_tab[n].name != NULL)
	{
		if (be_oper(g_op_tab[n++].name, f))
			return (n);
	}
	return (0);
}

static t_list	*take_name(char *f, int *i, int siz, t_list *list)
{
	int		n;
	t_list	*label;

	n = 0;
	while (check_char(f[*i]) == 1)
	{
		*i += 1;
		n++;
	}
	if (f[*i] != LABEL_CHAR || (n == 0 && (f[*i] = '.')))
		close_lex(f, *i - n);
	label = (t_list *)malloc(sizeof(t_list));
	label->next = list;
	label->str = (char *)malloc(n + 1);
	label->str[n] = '\0';
	*i -= n;
	n = 0;
	while (f[*i] != LABEL_CHAR)
		label->str[n++] = f[(*i)++];
	label->n = siz;
	*i += 1;
	return (label);
}

t_list			*take_operat_or_name(int i, t_asm *as)
{
	t_list	*labels;
	int		op;

	labels = NULL;
	while (as->f[i] != '\0')
	{
		while (as->f[i] == ' ' || as->f[i] == '\t' || as->f[i] == '\n')
			i++;
		if (as->f[i] == '\0')
			break ;
		if (as->f[i] == COMMENT_CHAR || as->f[i] == SEPAR)
		{
			while (as->f[i] != '\n')
				i++;
		}
		else if ((op = take_oper(as->f + i)) == 0)
			labels = take_name(as->f, &i, as->size, labels);
		else
		{
			translate_opers(i, op, as);
			while (as->f[i] != '\n' && as->f[i] != '\0')
				i++;
		}
	}
	return (labels);
}
