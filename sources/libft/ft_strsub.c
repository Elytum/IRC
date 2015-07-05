/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 05:29:53 by achazal           #+#    #+#             */
/*   Updated: 2014/11/23 01:01:39 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*new;
	size_t		c;

	c = 0;
	if (s)
	{
		if (!(new = ft_strnew(len)))
			return (NULL);
		c = 0;
		while (c < len)
		{
			new[c] = s[start + c];
			c++;
		}
		return (new);
	}
	return (NULL);
}
