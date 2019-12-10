/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:22:16 by crath             #+#    #+#             */
/*   Updated: 2019/05/30 12:22:28 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define HH_FLAG			0x00000001
# define H_FLAG				0x00000002
# define L_FLAG				0x00000004
# define LL_FLAG			0x00000008
# define LEFTFORMAT_FLAG	0x00000010
# define SHOWSIGN_FLAG		0x00000020
# define HASH_FLAG			0x00000040
# define ZERO_FLAG			0x00000080
# define SIGNED_FLAG		0x00000100
# define CAPS_FLAG			0x00000200
# define SPACE_FLAG			0x00000400
# define POS_FLAG			0x00000800
# define NEG_FLAG			0x00001000
# define J_FLAG				0x00002000
# define Z_FLAG				0x00004000
# define WIDTH				0x00100000
# define PRECISION			0x00200000
# define NOT_SPEC			0x00400000

# define SPECIFICATOR		"cCsSpdDiuUoOxXfF%"

# define BASE				0x7FF0000000000000
# define MANTIS				0x000FFFFFFFFFFFFF

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

typedef struct	s_format
{
	char		spec;
	unsigned	flags;
	int			width;
	int			precision;
}				t_format;

typedef struct	s_float
{
	long double	x;
	char		spec_value;
	char		sign;
}				t_float;

int				ft_putchar(char c);
int				ft_putnchar(char c, size_t size);
int				ft_putstr(char *s);
int				ft_putwchar(wchar_t wc);
int				ft_wcharlen(wchar_t wc);
int				ft_putwstr(wchar_t *ws, int size);
int				ft_wstrlen(wchar_t *ws);

void			ft_memcpy(void *dst, const void *src, size_t n);

int				ft_printf(const char *fmt, ...);
size_t			ft_strlen(char *str);
char			*ft_strdup(const char *str);
char			*ft_strnew(size_t size);
char			*ft_itoa(long n);
char			*ft_strjoin(char *s1, char *s2);
long			ft_power(int base, int power);
int				ft_minus_flag(char *res, t_format *lst, t_float *flt);

int				ft_print_c(t_format f, va_list av);
int				ft_print_s(t_format *f, va_list av);
int				ft_print_p(t_format *f, va_list av);
int				ft_print_f(t_format *f, va_list av);

int				ft_print_num(t_format *f, va_list av);
int				ft_print_dec(unsigned long long n, t_format *f);
int				ft_print_oct(unsigned long long n, t_format *f);
int				ft_print_hex(unsigned long long n, t_format *f);

t_format		*ft_create_format(void);
int				ft_read_format(const char *fmt, t_format *f);
int				ft_print_format(t_format *fmt, va_list args);

#endif
