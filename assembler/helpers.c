/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		str_len(char *str)
{
	int l;

	l = 0;
	while (str[l])
		l++;
	return (l);
}

void	err_ex(char *errors)
{
	write(2, errors, str_len(errors));
	exit(1);
}

int		check_char(char c)
{
	const char	label_chars[] = LABEL_CHARS;
	int			i;

	i = 0;
	while (label_chars[i] != '\0')
	{
		if (label_chars[i++] == c)
			return (1);
	}
	return (0);
}

int		ui_cod(unsigned int n, int q, t_asm *as)
{
	as->code[q] = n >> 24 & 0xff;
	as->code[q + 1] = n >> 16 & 0xff;
	as->code[q + 2] = n >> 8 & 0xff;
	as->code[q + 3] = n & 0xff;
	return (4);
}

int		us_cod(unsigned short n, int q, t_asm *as)
{
	as->code[q] = n >> 8;
	as->code[q + 1] = n & 0xff;
	return (2);
}
