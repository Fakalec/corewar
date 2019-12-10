/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:31:03 by crath             #+#    #+#             */
/*   Updated: 2019/05/30 16:07:30 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		is_specificator(char c)
{
	char	*str;

	str = SPECIFICATOR;
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

static unsigned	read_flag(char ch, unsigned flags)
{
	if (ch == 'h')
		return ((flags & H_FLAG) ? HH_FLAG : H_FLAG);
	if (ch == 'l')
		return ((flags & L_FLAG) ? LL_FLAG : L_FLAG);
	if (ch == 'z')
		return (Z_FLAG);
	if (ch == 'j')
		return (J_FLAG);
	if (ch == '-')
		return (LEFTFORMAT_FLAG);
	if (ch == '+')
		return (SHOWSIGN_FLAG);
	if (ch == '#')
		return (HASH_FLAG);
	if (ch == ' ')
		return (SPACE_FLAG);
	if (ch == '0')
		return (ZERO_FLAG);
	return (0);
}

static int		read_number(const char *fmt, t_format *f)
{
	int		i;
	int		*num;

	i = 0;
	num = NULL;
	if (fmt[i] > '0' && fmt[i] <= '9')
	{
		f->flags |= WIDTH;
		num = &f->width;
	}
	else if (fmt[i] == '.')
	{
		f->flags |= PRECISION;
		i++;
		num = &f->precision;
	}
	if (num)
	{
		*num = 0;
		while (fmt[i] >= '0' && fmt[i] <= '9')
			*num = *num * 10 + fmt[i++] - '0';
	}
	return (i);
}

static int		read_specificator(char c, t_format *f)
{
	if (c == 'X' || c == 'F')
	{
		f->flags |= CAPS_FLAG;
		f->spec = c + 32;
	}
	else if (c == 'C' || c == 'S' || c == 'D' || c == 'O' || c == 'U')
	{
		f->flags |= L_FLAG;
		f->spec = c + 32;
	}
	else if (c == 'i')
		f->spec = 'd';
	else
		f->spec = c;
	if ((f->flags & PRECISION || f->flags & LEFTFORMAT_FLAG) && f->spec != 'f'
			&& f->spec != 'c' && f->spec != 's' && f->spec != '%')
		f->flags &= ~ZERO_FLAG;
	return (1);
}

int				ft_read_format(const char *fmt, t_format *format)
{
	int			offset;
	int			i;
	unsigned	flag;

	i = 1;
	offset = 1;
	while (fmt[i] != '\0')
	{
		while ((flag = read_flag(fmt[i], format->flags)) != 0)
		{
			format->flags |= flag;
			i++;
		}
		i += read_number(fmt + i, format);
		if (is_specificator(fmt[i]) && read_specificator(fmt[i++], format))
			break ;
		if (offset == i)
		{
			format->spec = fmt[i++];
			format->flags |= NOT_SPEC;
			break ;
		}
		offset = i;
	}
	return (i);
}
