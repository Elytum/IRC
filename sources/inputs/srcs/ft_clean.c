/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 08:34:03 by achazal           #+#    #+#             */
/*   Updated: 2015/01/22 08:34:03 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inputs.h>

int			ft_clear_input(t_env *e)
{
	int		len;

	len = e->index;
	if (((ft_strlen(e->name) + ft_strlen(e->str)) % tgetnum("co")) == 0)
	{
		len--;
		tputs(tgetstr("bl", (char **)(&e->buf)), 1, ft_putc);
	}
	while (len--)
		tputs(tgetstr("le", (char **)(&e->buf)), 1, ft_putc);
	tputs(tgetstr("cd", (char **)(&e->buf)), 1, ft_putc);
	return (0);
}

void		ft_clean_histo(t_env *e)
{
	t_str	*ptr;

	ptr = e->histo;
	while (ptr)
	{
		if (ptr->tmp)
		{
			free(ptr->tmp);
			ptr->tmp = NULL;
		}
		ptr = ptr->next;
	}
}
