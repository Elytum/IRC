/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 21:39:25 by achazal           #+#    #+#             */
/*   Updated: 2015/03/04 21:39:27 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inputs.h>

void			ft_goleft(t_env *e)
{
	int			n;

	if (e->str[e->index - 1] == '\t')
		n = 1;
	else
		n = 1;
	// if (tgetflag("bw"))
	// {
		while (n-- > 0)
		{
			tputs(tgetstr("le", (char **)(&e->buf)), 1, ft_putc);
			e->index--;
		}
	// }
}

void			ft_goright(t_env *e)
{
	int			n;
	char		tmp[2];

	if (e->str[e->index] == '\t')
		n = 1;
	else
		n = 1;
	while (n-- > 0)
	{
		tmp[1] = '\0';
		tmp[0] = e->str[e->index++];
		tputs(tmp, 1, ft_putc);
	}
}
