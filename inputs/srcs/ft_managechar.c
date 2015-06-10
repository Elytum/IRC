/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_managechar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 08:14:16 by achazal           #+#    #+#             */
/*   Updated: 2015/02/06 14:08:43 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inputs.h>

static void	ft_process_fchar(t_env *e, char *inputs)
{
	char	*tmp;

	tmp = ft_strjoin(e->str, inputs);
	free(e->str);
	e->str = tmp;
	tmp = NULL;
	tputs(inputs, 1, ft_putc);
}

static void	ft_process_lchar(t_env *e, char *inputs)
{
	char	*tmp;
	char	*tmp2;
	size_t	len;
	int		flag;

	tputs(tgetstr("cd", (char **)(&e->buf)), 1, ft_putc);
	tmp2 = ft_strndup(e->str, e->index);
	tmp = ft_strjoin(tmp2, inputs);
	free(tmp2);
	tmp2 = ft_strjoin(tmp, e->str + e->index);
	free(tmp);
	free(e->str);
	e->str = tmp2;
	tputs(e->str + e->index, 1, ft_putc);
	flag = ((int)(e->max + ft_strlen(e->name)) %
		tgetnum("co") == (int)tgetnum("co") - 1);
	len = e->index + flag;
	e->index = e->max;
	while (len != e->index)
		ft_goleft(e);
	e->index -= flag;
}

static int	ft_process_char2(t_env *e, char *inputs)
{
	if (e->index == e->max)
		ft_process_fchar(e, inputs);
	else
		ft_process_lchar(e, inputs);
	e->max++;
	e->index++;
	return (1);
}

static int	ft_process_charloop(t_env *e, char *inputs)
{
	int		i;
	char	tmp[2];

	tmp[1] = '\0';
	i = 0;
	while (inputs[i] && i < 7)
	{
		if (inputs[i] <= 127)
		{
			if (inputs[i] == 9)
				inputs[i] = ' ';
			tmp[0] = inputs[i];
			inputs[i] = '\0';
			ft_process_char2(e, tmp);
		}
		i++;
	}
	return (i);
}

int			ft_process_char(t_env *e, char *inputs)
{
	if (ft_process_charloop(e, inputs) == 7)
	{
		while ((read(0, inputs, 7)) != EOF)
		{
			if (inputs[0] == 3 || inputs[0] == 4 || inputs[0] == 10)
				return (ft_quit(e, inputs));
			if (ft_delete(e, inputs))
				return (2);
			if (ft_arrows(e, inputs))
				return (2);
			if (ft_clear(e, inputs))
				return (2);
			ft_process_charloop(e, inputs);
			ft_bzero(inputs, 7);
		}
	}
	return (2);
}
