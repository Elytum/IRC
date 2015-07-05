/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 17:45:25 by achazal           #+#    #+#             */
/*   Updated: 2014/11/10 14:07:07 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	char	*str;
	int		pos;
	int		tmp;

	pos = 0;
	tmp = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (!(str = (char *)malloc(sizeof(char) * 12)))
		return (NULL);
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		str[pos++] = (n % 10) + 48;
		n = n / 10;
	}
	str[pos] = '\0';
	if (tmp < 0)
		str[pos++] = '-';
	str[pos] = '\0';
	return (ft_strrev(str));
}
