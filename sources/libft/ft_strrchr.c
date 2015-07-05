/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 19:27:39 by achazal           #+#    #+#             */
/*   Updated: 2014/11/10 14:27:26 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	test;
	size_t	counter;

	counter = ft_strlen(s);
	test = (char)c;
	while (counter > 0 && s[counter] != test)
		counter--;
	if (s[counter] == test)
		return ((char *)s + counter);
	else
		return (NULL);
}
