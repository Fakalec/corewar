/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_argument.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		validate_argument(char *f, int i)
{
	while (f[i] && f[i] != '\n')
	{
		if (f[i] == COMMENT_CHAR || f[i] == SEPAR)
			break ;
		if (f[i++] == SEPARATOR_CHAR)
			close_lex(f, i);
	}
}
