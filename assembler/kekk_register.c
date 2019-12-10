/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_regis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_end(char c)
{
	return (c == SEPARATOR_CHAR || c == '\n'
		|| c == COMMENT_CHAR || c == SEPAR);
}

int			check_regis(char *f, int i)
{
	if (f[i++] == 'r')
	{
		if (f[i] >= '0' && f[i] <= '9' && ++i)
		{
			if (f[i] >= '0' && f[i] <= '9' && ++i)
			{
				while (f[i] == ' ' || f[i] == '\t')
					i++;
				return (check_end(f[i]));
			}
			while (f[i] == ' ' || f[i] == '\t')
				i++;
			return (check_end(f[i]));
		}
	}
	return (0);
}

int			check_norm(char *f, int i)
{
	if (f[i++] == DIRECT_CHAR)
	{
		if ((f[i] >= '0' && f[i] <= '9') || f[i] == '-')
		{
			if (f[i] == '-')
				i++;
			while (f[i] >= '0' && f[i] <= '9')
				i++;
			while (f[i] == ' ' || f[i] == '\t')
				i++;
			return (check_end(f[i]));
		}
		else if (f[i] == LABEL_CHAR && ++i)
		{
			while (check_char(f[i]))
				i++;
			while (f[i] == ' ' || f[i] == '\t')
				i++;
			return (check_end(f[i]));
		}
		return (0);
	}
	return (0);
}

int			check_wrong(char *f, int i)
{
	if ((f[i] >= '0' && f[i] <= '9') || f[i] == '-')
	{
		if (f[i] == '-')
			i++;
		while (f[i] >= '0' && f[i] <= '9')
			i++;
		while (f[i] == ' ' || f[i] == '\t')
			i++;
		return (check_end(f[i]));
	}
	else if (f[i] == LABEL_CHAR && ++i)
	{
		while (check_char(f[i]))
			i++;
		while (f[i] == ' ' || f[i] == '\t')
			i++;
		return (check_end(f[i]));
	}
	return (0);
}
