/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:41:59 by crath             #+#    #+#             */
/*   Updated: 2019/05/30 15:42:01 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_wstrlen(wchar_t *ws)
{
	int		ws_len;
	int		wc_len;

	if (ws == NULL)
		return (-1);
	ws_len = 0;
	while (*ws)
	{
		if ((wc_len = ft_wcharlen(*ws)) == -1)
			return (-1);
		ws_len += wc_len;
		ws++;
	}
	return (ws_len);
}
