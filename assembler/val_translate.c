/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_translate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				str_cmp(char *a, char *b)
{
	while (*a && *b && *a == *b)
	{
		a++;
		b++;
	}
	return (*a == '\0');
}

static void		seek_oper_name(t_list *na, t_list *names, t_asm *as)
{
	int		i;

	while (names)
	{
		i = 0;
		while (na->str[i] && names->str[i] && na->str[i] == names->str[i])
			i++;
		if (na->str[i] == '\0' && names->str[i] == '\0')
		{
			if (na->name_len == 2)
				us_cod(names->n - na->n, na->p, as);
			else
				ui_cod(names->n - na->n, na->p, as);
			break ;
		}
		names = names->next;
	}
	if (names == NULL)
	{
		write(2, "Error: label ", 13);
		write(2, na->str, str_len(na->str));
		write(2, " not found\n", 11);
		exit(1);
	}
}

static void		take_cod(int i, t_asm *as)
{
	t_list	*labels_head;
	t_list	*op_labels;

	if (str_len(as->name) > PROG_NAME_LENGTH)
		err_ex("Error: champion name is too long\n");
	if (str_len(as->comment) > COMMENT_LENGTH)
		err_ex("Error: champion comment is too long\n");
	labels_head = take_operat_or_name(i, as);
	op_labels = as->op_labels;
	while (op_labels)
	{
		seek_oper_name(op_labels, labels_head, as);
		op_labels = op_labels->next;
	}
	if (as->size == 0)
		err_ex("Error: can't create empty champion\n");
	while (labels_head)
	{
		op_labels = labels_head;
		labels_head = labels_head->next;
		free(op_labels->str);
		free(op_labels);
	}
}

static char		*take_comm(char *f, int *i, char *separ_nm)
{
	int		n;
	int		j;
	char	*str;

	j = 0;
	while (f[*i] == separ_nm[j++])
		*i += 1;
	while (f[*i] == ' ' || f[*i] == '\t')
		*i += 1;
	if (f[*i] != '"')
		close_lex(f, *i);
	n = *i + 1;
	while (f[n] != '"' && f[n])
		n++;
	if (f[n] != '"')
		close_lex(f, n);
	str = (char *)malloc(n - *i);
	j = 0;
	while (++(*i) < n)
		str[j++] = f[*i];
	str[j] = '\0';
	*i += 1;
	return (str);
}

int				val_translate(t_asm *as)
{
	int i;

	i = 0;
	while (as->f[i])
	{
		while (as->f[i] == ' ' || as->f[i] == '\t' || as->f[i] == '\n')
			i++;
		if (as->f[i] == COMMENT_CHAR || as->f[i] == SEPAR)
		{
			while (as->f[i] != '\n' && as->f[i])
				i++;
		}
		else if (as->name == NULL && str_cmp(NAME_CMD_STRING, as->f + i))
			as->name = take_comm(as->f, &i, NAME_CMD_STRING);
		else if (as->comment == NULL && str_cmp(COMMENT_CMD_STRING, as->f + i))
			as->comment = take_comm(as->f, &i, COMMENT_CMD_STRING);
		else
			close_lex(as->f, i);
		if (as->name && as->comment)
		{
			take_cod(i, as);
			return (0);
		}
	}
	return (1);
}
