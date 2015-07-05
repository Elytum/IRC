/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrarray_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 06:38:01 by achazal           #+#    #+#             */
/*   Updated: 2014/11/08 13:53:04 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putstrarray_fd(char **str, int fd)
{
	size_t	i;

	i = 0;
	if (str && str[i])
	{
		ft_putchar_fd('{', fd);
		while (str[i])
		{
			ft_putstr_fd(" \"", fd);
			ft_putstr_fd(str[i], fd);
			ft_putstr_fd("\",", fd);
			i++;
		}
		ft_putstr_fd("\b }", fd);
	}
}
