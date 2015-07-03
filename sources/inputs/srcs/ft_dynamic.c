/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 08:35:52 by achazal           #+#    #+#             */
/*   Updated: 2015/01/22 08:35:53 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inputs.h>

static t_env		*sing_env(t_env *var)
{
	static t_env	*ptr = NULL;

	if (var)
		ptr = var;
	return (ptr);
}

char				*ft_dynamic_get(void)
{
	static t_env	*e = NULL;
	char			inputs[7];
	int				value;
	static int		initialized = 0;
	char			*ptr;

	ft_bzero(inputs, 7);
	if (initialized == 0)
	{
		initialized = 1;
		if (!e && (!(e = (t_env *)ft_memalloc(sizeof(t_env)))))
			exit(0);
		sing_env(e);
		e->index = 0;
		e->max = 0;
		if (!(e->str = (char *)ft_memalloc(sizeof(char))))
			return (NULL);
		ft_clean_histo(e);
		ft_lstr_inputsinit(e);
		e->buf = start_termcaps();
		e->name = "";
	}
	if ((read(0, inputs, 7)) != EOF)
		value = ft_manage_inputs(e, inputs);
	if (value >= 0)
	{
		ft_lstr_inputsinit(e);
		e->index = 0;
		e->max = 0;
		ptr = e->str;
		if (!(e->str = (char *)ft_memalloc(sizeof(char))))
			return (NULL);
		return (ptr);
	}
	else
		return (NULL);
}

void			ft_dynamic_pause(void)
{
	pause_termcaps();
}

void			ft_dynamic_clean(void)
{
	t_env		*e;

	e = sing_env(NULL);
	if (e && e->str)
	{
		e->save = e->index;
		while (e->index > 0)
			ft_goleft(e);
		tputs(tgetstr("cd", (char **)(&e->buf)), 1, ft_putc);
	}
}

void			ft_dynamic_restore(void)
{
	t_env		*e;

	e = sing_env(NULL);
	if (e && e->str)
	{
		tputs(e->str, 1, ft_putc);
		e->index = e->max;
		while (e->index > e->save)
			ft_goleft(e);
	}
}