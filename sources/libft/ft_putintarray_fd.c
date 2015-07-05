/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putintarray_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 17:56:48 by achazal           #+#    #+#             */
/*   Updated: 2014/11/18 15:03:59 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putintarray_fd(int *array, size_t size, int fd)
{
	size_t	c;

	c = 0;
	if (size > 0)
	{
		ft_putstr_fd("{ ", fd);
		while (c < size)
		{
			ft_putnbr_fd(array[c], fd);
			ft_putstr_fd(" , ", fd);
			c++;
		}
		ft_putstr_fd("\b\b}", fd);
	}
}
