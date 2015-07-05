/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 18:10:52 by achazal           #+#    #+#             */
/*   Updated: 2014/11/23 03:26:30 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strdup(const char *str)
{
	register char	*strnew;
	register char	*ptr;

	strnew = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	ptr = strnew;
	while (*str)
		*ptr++ = *str++;
	*ptr = '\0';
	return (strnew);
}
