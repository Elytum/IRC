/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:49:30 by achazal           #+#    #+#             */
/*   Updated: 2015/01/03 00:36:03 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sc;

	if (!(sc = (unsigned char *)s))
		return (NULL);
	while (n--)
	{
		if (*sc == (unsigned char)c)
			return (sc);
		sc++;
	}
	return (NULL);
}
