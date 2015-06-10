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

int					ft_quit(t_env *e, char *inputs)
{
	if (inputs[0] == 3)
		return (0);
	else if (inputs[0] == 10)
	{
		if (e->histo->str)
			free(e->histo->str);
		e->histo->str = ft_strdup(e->str);
		ft_endline(e);
		return (1);
	}
	else if (inputs[0] == 4)
	{
		if (e->histo->str)
			free(e->histo->str);
		e->histo->str = ft_strdup(e->str);
		ft_endline(e);
		return (0);
	}
	return (0);
}

int					ft_delete(t_env *e, char *inputs)
{
	if (inputs[0] == 27 && inputs[1] == 91 && inputs[2] == 51 &&
	(inputs[3] == 126 && inputs[4] == 0))
	{
		ft_process_back_delete(e);
		return (1);
	}
	if (inputs[0] == 127 && inputs[1] == 0 && inputs[2] == 0)
	{
		ft_process_delete(e);
		return (1);
	}
	return (0);
}

static void			ft_lstr_inputsinit(t_env *e)
{
	if (!(e->histo))
		ft_lststr_add(&(e->histo), ft_lststr_new(""));
	e->phisto = e->histo;
	if (e->phisto->str && (*(e->phisto->str)))
	{
		ft_lststr_add(&(e->histo), ft_lststr_new(""));
		e->phisto = e->histo;
	}
}

static int			ft_manage_inputs(t_env *e, char *inputs)
{
	int				value;

	if ((inputs[0] == 4 || inputs[0] == 10) &&
		inputs[1] == 0 && inputs[2] == 0 && inputs[3] == 0 &&
		inputs[4] == 0 && inputs[5] == 0 && inputs[6] == 0)
		return (ft_quit(e, inputs));
	else if (!ft_delete(e, inputs))
		if (!ft_arrows(e, inputs))
			if (!ft_clear(e, inputs))
				if (ft_isprint(inputs[0]) || inputs[0] == 9)
					if ((value = ft_process_char(e, inputs)) != 2)
						return (value);
	return (-1);
}

char				*ft_get_inputs(char *str)
{
	static t_env	*e = NULL;
	char			inputs[7];
	int				value;

	if (!e && (!(e = (t_env *)ft_memalloc(sizeof(t_env)))))
		exit (0);
	e->name = str;
	e->index = 0;
	e->max = 0;
	if (!(e->str = (char *)ft_memalloc(sizeof(char))))
		return (NULL);
	ft_bzero(inputs, 7);
	ft_clean_histo(e);
	ft_lstr_inputsinit(e);
	tputs(e->name, 1, ft_putc);
	e->buf = start_termcaps();
	while ((read(0, inputs, 7)) != EOF)
	{
		if ((value = ft_manage_inputs(e, inputs)) >= 0)
			return (e->str);
		ft_bzero(inputs, 7);
	}
	pause_termcaps();
	ft_endline(e);
	return (e->str);
}
