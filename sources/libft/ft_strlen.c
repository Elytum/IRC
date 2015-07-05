/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 18:07:27 by achazal           #+#    #+#             */
/*   Updated: 2015/01/03 00:14:36 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t				ft_strlen(const char *str)
{
	register char	*ptr;

	ptr = (char *)str;
	while (*ptr)
		ptr++;
	return (ptr - str);
}
