/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:21:35 by crath             #+#    #+#             */
/*   Updated: 2019/05/30 12:21:44 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_format	*ft_create_format(void)
{
	t_format	*format;

	format = (t_format*)malloc(sizeof(t_format));
	if (format)
	{
		format->spec = 0;
		format->flags = 0;
		format->precision = 0;
		format->width = 0;
	}
	return (format);
}
