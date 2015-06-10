/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 08:09:40 by achazal           #+#    #+#             */
/*   Updated: 2015/01/22 08:09:40 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inputs.h>

int			ft_process_delete(t_env *e)
{
	char	*tmp;

	if (e->index > 0)
	{
		ft_goleft(e);
		tputs(tgetstr("sc", (char **)(&e->buf)), 1, ft_putc);
		e->index++;
		e->str[e->index - 1] = '\0';
		tmp = ft_strjoin(e->str, e->str + e->index);
		free(e->str);
		e->str = tmp;
		e->max--;
		e->index--;
		tputs(e->str + e->index, 1, ft_putc);
		tputs(" \0", 1, ft_putc);
		tputs(tgetstr("rc", (char **)(&e->buf)), 1, ft_putc);
	}
	return (0);
}

int			ft_process_back_delete(t_env *e)
{
	char	*tmp;

	if (e->index < e->max)
	{
		tputs(tgetstr("sc", (char **)(&e->buf)), 1, ft_putc);
		e->str[e->index] = '\0';
		tmp = ft_strjoin(e->str, e->str + e->index + 1);
		free(e->str);
		e->str = tmp;
		e->max--;
		tputs(e->str + e->index, 1, ft_putc);
		tputs(" \0", 1, ft_putc);
		tputs(tgetstr("rc", (char **)(&e->buf)), 1, ft_putc);
	}
	return (0);
}

static int	ft_ctrlk(t_env *e)
{
	char	*tmp;

	if (e->index < e->max)
	{
		ft_clear_input(e);
		tputs(tgetstr("cd", (char **)(&e->buf)), 1, ft_putc);
		e->str[e->index] = '\0';
		tmp = ft_strdup(e->str);
		free(e->str);
		e->str = tmp;
		e->max = ft_strlen(e->str);
		tputs(e->str, 1, ft_putc);
	}
	return (1);
}

static int	ft_ctrll(t_env *e)
{
	size_t	mem;

	tputs(tgetstr("cl", (char **)(&e->buf)), 1, ft_putc);
	tputs(e->name, 1, ft_putc);
	tputs(e->str, 1, ft_putc);
	mem = e->index;
	e->index = e->max;
	while (mem != e->index)
		ft_goleft(e);
	return (1);
}

int			ft_clear(t_env *e, char *inputs)
{
	if (inputs[0] == 11 && inputs[1] == 0 && inputs[2] == 0)
		return (ft_ctrlk(e));
	if (inputs[0] == 12 && inputs[1] == 0 && inputs[2] == 0)
		return (ft_ctrll(e));
	return (0);
}
