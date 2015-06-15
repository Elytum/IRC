/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 08:32:07 by achazal           #+#    #+#             */
/*   Updated: 2015/01/22 08:32:07 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inputs.h>

int		ft_putc(int c)
{
	write(1, &c, 1);
	return (1);
}

void	ft_put_histo(t_env *e)
{
	t_str *ptr;

	ptr = e->histo;
	tputs("\nThe historic is :\n", 1, ft_putc);
	while (ptr)
	{
		if (ptr->str)
		{
			tputs(ptr->str, 1, ft_putc);
			tputs("\n", 1, ft_putc);
		}
		ptr = ptr->next;
	}
	tputs("\n", 1, ft_putc);
}
