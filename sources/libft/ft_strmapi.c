/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 07:25:11 by achazal           #+#    #+#             */
/*   Updated: 2014/11/10 14:04:46 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new;
	unsigned int	i;

	if (s && f)
	{
		i = 0;
		new = ft_strdup(s);
		while (new[i])
		{
			new[i] = f(i, new[i]);
			i++;
		}
		return (new);
	}
	if (s)
		return (ft_strdup(s));
	return (NULL);
}
