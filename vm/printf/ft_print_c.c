/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:26:31 by crath             #+#    #+#             */
/*   Updated: 2019/05/30 12:26:43 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static int	print_spaces(int width, unsigned flags)
{
	char	filler;
	int		len;

	len = 0;
	if (flags & WIDTH)
	{
		len = width - 1;
		if ((flags & ZERO_FLAG) && !(flags & LEFTFORMAT_FLAG))
			filler = '0';
		else
			filler = ' ';
		ft_putnchar(filler, len);
	}
	return (len);
}

static int	print_wc_spaces(int width, int wc_len)
{
	int		len;

	len = 0;
	if (width > wc_len)
	{
		len = width - wc_len;
		ft_putnchar(' ', len);
	}
	return (len);
}

int			ft_print_wc(t_format f, wchar_t wch)
{
	int		len;
	int		wc_len;

	len = 0;
	if ((wc_len = ft_wcharlen(wch)) == -1)
		return (-1);
	if ((f.flags & WIDTH) && !(f.flags & LEFTFORMAT_FLAG))
		len += print_wc_spaces(f.width, wc_len);
	len += ft_putwchar(wch);
	if ((f.flags & WIDTH) && (f.flags & LEFTFORMAT_FLAG))
		len += print_wc_spaces(f.width, wc_len);
	return (len);
}

int			ft_print_c(t_format f, va_list av)
{
	int		len;

	len = 0;
	if (f.flags & L_FLAG)
		return (ft_print_wc(f, va_arg(av, wchar_t)));
	if (!(f.flags & LEFTFORMAT_FLAG))
		len += print_spaces(f.width, f.flags);
	if (f.spec == '%' || f.flags & NOT_SPEC)
		len += ft_putchar(f.spec);
	else
		len += ft_putchar((char)va_arg(av, int));
	if (f.flags & LEFTFORMAT_FLAG)
		len += print_spaces(f.width, f.flags);
	return (len);
}
