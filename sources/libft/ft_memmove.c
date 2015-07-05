/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 10:43:01 by achazal           #+#    #+#             */
/*   Updated: 2014/11/08 16:50:31 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memmove(void *dst, const void *src, size_t len)
{
	char	*cp;

	cp = (char *)malloc(sizeof(char) * (len + 1));
	cp = ft_memcpy(cp, src, len);
	return (ft_memcpy(dst, cp, len));
}
