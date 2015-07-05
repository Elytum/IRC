/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 04:26:59 by achazal           #+#    #+#             */
/*   Updated: 2014/11/17 18:21:00 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrev(char *str)
{
	char	*dst;
	int		len;
	int		i;

	len = ft_strlen(str);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		dst[i] = str[len - i - 1];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
