/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:32:13 by achazal           #+#    #+#             */
/*   Updated: 2014/11/07 04:32:12 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*way1;
	char	*way2;

	way1 = (char *)dst;
	way2 = (char *)src;
	while (n--)
		*way1++ = *way2++;
	return (dst);
}
