/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:30:24 by crath             #+#    #+#             */
/*   Updated: 2019/05/30 15:30:34 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_putwstr(wchar_t *ws, int size)
{
	int		ws_len;
	int		wchar_len;

	if (ws == NULL)
		return (-1);
	ws_len = 0;
	while (*ws)
	{
		if ((wchar_len = ft_putwchar(*ws)) == -1)
			return (-1);
		ws_len += wchar_len;
		if (ws_len == size)
			return (ws_len);
		ws++;
	}
	return (ws_len);
}
