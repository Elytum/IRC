/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 20:07:01 by achazal           #+#    #+#             */
/*   Updated: 2014/11/13 20:06:32 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!ft_strlen(s2))
		return ((char *)s1);
	if (ft_strlen(s2) > ft_strlen(s1))
		return (NULL);
	while (s1[i] && s2[i] && n--)
	{
		i = 0;
		while (s2[i] != '\0' && s1[i] == s2[i] && (n - i + 1) > 0)
			i++;
		if (!s2[i])
			return ((char *)s1);
		s1++;
	}
	return (NULL);
}
