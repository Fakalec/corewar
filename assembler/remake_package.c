/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remake_package.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			init_struct(t_asm *as)
{
	as->name = NULL;
	as->comment = NULL;
	as->size = 0;
	as->op_labels = NULL;
}

void			free_every(t_asm *as)
{
	t_list *tmp;

	while (as->op_labels)
	{
		tmp = as->op_labels;
		as->op_labels = as->op_labels->next;
		free(tmp->str);
		free(tmp);
	}
	free(as->f);
	free(as->comment);
	free(as->name);
	free(as->cor_f_name);
}

static void		take_file(char *d, char *f, char *val)
{
	int i;
	int n;

	i = -1;
	while (d[++i])
		val[i] = d[i];
	val[i++] = '/';
	n = 0;
	while (f[n])
		val[i++] = f[n++];
	val[i] = '\0';
}

void			remake_package(char *pack_name, t_asm *as)
{
	struct dirent	*pack;
	char			val[512];
	DIR				*d;
	int				len;

	d = opendir(pack_name);
	if (d == NULL)
		err_ex("Error: bad directory name\n");
	while ((pack = readdir(d)))
	{
		len = str_len(pack->d_name);
		if (pack->d_name[0] == '.' || len < 3 || pack->d_name[len - 1] != 's'
			|| pack->d_name[len - 2] != '.')
			continue ;
		init_struct(as);
		take_file(pack_name, pack->d_name, val);
		input_file(val, as);
		if (val_translate(as))
			err_ex("Error: empty source f\n");
		make_dot_cor(val, as);
		output_dot_cor(as);
		free_every(as);
	}
	closedir(d);
}
