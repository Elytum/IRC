/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 04:34:07 by achazal           #+#    #+#             */
/*   Updated: 2014/11/07 04:55:18 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strisin(char *s, char **array)
{
	int	c;

	c = 0;
	while (array[c][0])
		if (strcmp(s, array[c]))
			return (1);
	return (0);
}
