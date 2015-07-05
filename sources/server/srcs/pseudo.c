#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "server.h"
#include "client.h"

char			*itoa(int i, char b[])
{
	const char	digit[] = "0123456789";
	char		*p;
	int			shifter;

	shifter = i;
	p = b;
	if (i < 0)
	{
		*p++ = '-';
		i *= -1;
	}
	while (shifter)
	{
		++p;
		shifter /= 10;
	}
	*p = '\0';
	while (i)
	{
		*(--p) = digit[i % 10];
		i /= 10;
	}
	return (b);
}

static int			char_seek(const char *str, const char *chars)
{
	char			*ptr;

	ptr = (char *)chars;
	while (*ptr)
	{
		if (strchr(str, *ptr))
			return (1);
		++ptr;
	}
	return (0);
}

static void			send_pseudo_error(const SOCKET sock, const char *s1, const char *s2)
{
	char			*str;
	size_t			s1_len;
	size_t			s2_len;

	s1_len = strlen(s1);
	s2_len = strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * (s1_len + s2_len + sizeof(PSEUDO_ERROR)))))
		return ;
	memcpy(str, s1, s1_len);
	memcpy(str + s1_len, s2, s2_len);
	memcpy(str + s1_len + s2_len, PSEUDO_ERROR, sizeof(PSEUDO_ERROR));
	send_string(sock, str, s1_len + s2_len + sizeof(PSEUDO_ERROR));
	free(str);
}

int					pseudo_error(t_client *client)
{
	char			len_string[32];

	if (client->name_len < NAME_MIN_SIZE)
	{
		send_pseudo_error(client->sock, PSEUDO_ERROR_NAMETOOSHORT, itoa(NAME_MIN_SIZE, len_string));
		return (1);
	}
	else if (client->name_len > NAME_SIZE)
	{
		send_pseudo_error(client->sock, PSEUDO_ERROR_NAMETOOLONG, itoa(NAME_SIZE, len_string));
		return (1);
	}
	else if (char_seek(client->name, EXCLUDED_CHARACTERS))
	{
		send_pseudo_error(client->sock, PSEUDO_ERROR_INVALIDCHARACTER, "");
		return (1);
	}
	return (0);
}