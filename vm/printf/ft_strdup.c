/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crath <crath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:31:38 by crath             #+#    #+#             */
/*   Updated: 2019/05/30 15:31:40 by crath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*str;

	size = ft_strlen((char*)s1);
	str = (char*)malloc(size * sizeof(char) + 1);
	if (!str)
		return (NULL);
	str[size] = 0;
	while (size--)
		str[size] = s1[size];
	return (str);
}
