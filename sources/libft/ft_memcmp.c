/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:53:02 by achazal           #+#    #+#             */
/*   Updated: 2014/11/13 19:49:31 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*w1;
	unsigned char	*w2;

	w1 = (unsigned char *)s1;
	w2 = (unsigned char *)s2;
	if (!w1 || !w2 || n == 0)
		return (0);
	while (--n && *w1 == *w2)
	{
		w1++;
		w2++;
	}
	return (*w1 - *w2);
}
