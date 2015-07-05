/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 20:20:13 by achazal           #+#    #+#             */
/*   Updated: 2014/11/10 18:11:29 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int	value;
	int	sign;

	sign = 1;
	if (!str)
		return (0);
	while (ft_isspace(str[0]) || str[0] == '\v' ||
			str[0] == '\f' || str[0] == '\r')
		str++;
	if (str[0] == '+')
		str++;
	else if (str[0] == '-')
	{
		sign = -1;
		str++;
	}
	value = 0;
	while (str[0] && ft_isdigit(str[0]))
	{
		value = value * 10 + str[0] - '0';
		str++;
	}
	return (value * sign);
}
