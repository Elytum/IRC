/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 18:58:54 by achazal           #+#    #+#             */
/*   Updated: 2014/11/07 15:55:39 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	len;
	size_t	c;

	len = ft_strlen(s1);
	c = 0;
	while (n-- > 0 && s2[c])
	{
		s1[len + c] = s2[c];
		c++;
	}
	s1[len + c] = '\0';
	return (s1);
}
