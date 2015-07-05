/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 04:24:35 by achazal           #+#    #+#             */
/*   Updated: 2014/11/10 03:43:53 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strtrim(char const *s)
{
	unsigned int	first;
	unsigned int	last;

	first = 0;
	if (s)
	{
		if (!ft_isspace(s[0]) || !ft_isspace(s[ft_strlen(s) - 1]))
			return (strdup(s));
		last = ft_strlen(s) - 1;
		while (s[first] && ft_isspace(s[first]))
			first++;
		while (last > 0 && ft_isspace(s[last]))
			last--;
		if (last < first)
			return (ft_strnew(0));
		return (ft_strsub(s, first, last - first + 1));
	}
	return (ft_strnew(0));
}
