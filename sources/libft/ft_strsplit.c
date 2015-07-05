/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 13:10:29 by achazal           #+#    #+#             */
/*   Updated: 2014/12/27 23:21:27 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char sep)
{
	size_t		ret;

	ret = 0;
	while (s && *s)
	{
		if (*s == sep)
			ret++;
		while (*s == sep)
			s++;
		s++;
	}
	return (ret);
}

static size_t	ft_strlen_ptr(char const *start, char const *end)
{
	if (!end)
		return (ft_strlen(start));
	return (((unsigned char*)end - (unsigned char *)start));
}

static char		*trim_chars(char *ptr, char c)
{
	while (ptr && *ptr == c)
		ptr++;
	return (ptr);
}

static char		*trim_word(char *ptr, char c)
{
	while (ptr && (*ptr != c) && *ptr)
		ptr++;
	return (ptr);
}

char			**ft_strsplit(char const *s, char c)
{
	char		*ptr;
	char		*orig;
	char		**ret;
	char		**p_ret;
	size_t		len;

	len = ft_count_words(s, c);
	ret = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	ptr = (char *)s;
	p_ret = ret;
	while (ptr && *ptr)
	{
		ptr = trim_chars(ptr, c);
		orig = ptr;
		ptr = trim_word(ptr, c);
		len = ft_strlen_ptr(orig, ptr);
		if (orig && p_ret && *orig)
			*p_ret++ = ft_strsub(orig, 0, len);
		if (!*ptr)
			break ;
		ptr++;
	}
	*p_ret = NULL;
	return (ret);
}
