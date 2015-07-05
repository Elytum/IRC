/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 02:40:00 by achazal           #+#    #+#             */
/*   Updated: 2014/11/23 03:25:18 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char					*ft_strndup(const char *str, size_t n)
{
	register char		*strnew;
	register char		*ptr;

	strnew = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	ptr = strnew;
	while (*str && n--)
		*ptr++ = *str++;
	*ptr = '\0';
	return (strnew);
}
