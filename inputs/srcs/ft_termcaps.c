/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 21:41:00 by achazal           #+#    #+#             */
/*   Updated: 2015/03/04 21:41:00 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define GET_SING 0
#define SET_SING 1
#define UNSET_SING 2
#define NEVERSET_SING 2
#include <inputs.h>

static int			termcaps_sing(int value)
{
	static int		sing = NEVERSET_SING;

	if (value != GET_SING)
		sing = value;
	return (sing);
}

static BYPASS		*old_term_sing(BYPASS *term)
{
	static BYPASS	*attr = NULL;

	if (!attr)
	{
		if (!(attr = (BYPASS *)malloc(sizeof(BYPASS))))
			exit(-1);
	}
	if (term)
		ft_memcpy(attr, term, sizeof(BYPASS));
	return (attr);
}

static BYPASS		*new_term_sing(BYPASS *term)
{
	static BYPASS	*attr = NULL;

	if (!attr)
	{
		if (!(attr = (BYPASS *)malloc(sizeof(BYPASS))))
			exit(-1);
	}
	if (term)
		ft_memcpy(attr, term, sizeof(BYPASS));
	return (attr);
}

void				pause_termcaps(void)
{
	int				sing;

	sing = termcaps_sing(GET_SING);
	if (sing == SET_SING)
	{
		tcsetattr(0, TCSADRAIN, old_term_sing(NULL));
		termcaps_sing(UNSET_SING);
	}
}

char				*start_termcaps(void)
{
	int				sing;
	BYPASS			term;
	static char		*buf = NULL;

	sing = termcaps_sing(GET_SING);
	if (sing == NEVERSET_SING)
	{
		if (!(buf = (char *)ft_memalloc(sizeof(char) * 2048)) ||
			tgetent(buf, NULL) < 1)
			exit(-1);
		tcgetattr(0, &term), old_term_sing(&term);
		term.c_lflag &= ~(ICANON);
		term.c_lflag &= ~(ECHO);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
		if (tcsetattr(0, TCSADRAIN, &term) == -1)
			exit(-1);
		tcgetattr(0, &term), new_term_sing(&term);
	}
	else if (sing == UNSET_SING)
	{
		tcsetattr(0, TCSADRAIN, new_term_sing(NULL));
		termcaps_sing(SET_SING);
	}
	termcaps_sing(SET_SING);
	return (buf);
}
