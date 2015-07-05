/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 18:54:00 by achazal           #+#    #+#             */
/*   Updated: 2014/11/07 11:41:12 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcat(char *s1, const char *s2)
{
	size_t	len;
	size_t	c;

	len = ft_strlen(s1);
	c = 0;
	while (s2[c])
	{
		s1[len + c] = s2[c];
		c++;
	}
	s1[len + c] = '\0';
	return (s1);
}
