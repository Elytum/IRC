/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 07:25:11 by achazal           #+#    #+#             */
/*   Updated: 2014/11/10 14:04:09 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*new;
	char	*ptr;

	if (s && f)
	{
		new = ft_strdup(s);
		ptr = new;
		while (*ptr)
		{
			*ptr = f(*ptr);
			ptr++;
		}
		return (new);
	}
	if (s)
		return (ft_strdup(s));
	return (NULL);
}
