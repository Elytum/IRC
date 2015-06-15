#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "server.h"
#include "client.h"

#define EXCLUDED_CHARACTERS "\n"

#define CONNECTION_STRING "Please enter your pseudo"
#define PSEUDO_ERROR_NAMETOOSHORT "Name too short, minimum"
#define PSEUDO_ERROR_NAMETOOLONG "Name too long, maximum "
#define PSEUDO_ERROR_INVALIDCHARACTER "Invalid character, name can't contain ("EXCLUDED_CHARACTERS")"
#define PSEUDO_ERROR ", please retype"

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
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
}

static int			pseudo_error(t_client *client)
{
	char			len_string[32];

	if (client->name_len < NAME_MIN_SIZE)
	{
		itoa(NAME_MIN_SIZE, len_string);
		send_pseudo_error(client->sock, PSEUDO_ERROR_NAMETOOSHORT, len_string);
		return (1);
	}
	else if (client->name_len > NAME_SIZE)
	{
		itoa(NAME_SIZE, len_string);
		send_pseudo_error(client->sock, PSEUDO_ERROR_NAMETOOLONG, len_string);
		return (1);
	}
	else if (char_seek(client->name, EXCLUDED_CHARACTERS))
	{
		send_pseudo_error(client->sock, PSEUDO_ERROR_INVALIDCHARACTER, "");
		return (1);
	}
	return (0);
}

/*
**		Determine if the client is connecting or disconnecting and in case of connection, add it.
*/

int					client_status_update(const SOCKET sock, char buffer[BUF_SIZE], t_client *client)
{
	SOCKADDR_IN		csin = { 0 };
	socklen_t		sinsize = sizeof csin;
	int				csock = accept(sock, (SOCKADDR *)&csin, &sinsize);
	size_t			len;

	if (csock == SOCKET_ERROR)
	{
		perror("accept()");
		return (0);
	}
	client->sock = csock;
	client->message.content = NULL;
	send_string(client->sock, CONNECTION_STRING, sizeof(CONNECTION_STRING));
	client->name_len = 0;
	if ((client->name_len = read_client(client->sock, client->name, NAME_SIZE)) == -1)
		return (0);
	while (pseudo_error(client))
	{
		if ((client->name_len = read_client(client->sock, client->name, NAME_SIZE)) == -1)
			return (0);
	}
client->name[--client->name_len] = '\0';
	return (csock);
}

/*
**		Spread the word about the disconnection to every client except the disconnected one.
*/

void				disconnection(int *actual, t_client clients[MAX_CLIENTS], size_t i)
{
	t_client		disconnected;
	int				c;

	disconnected = clients[i];
	closesocket(clients[i].sock);
	remove_client(clients, i, actual);
	free(disconnected.message.content);
	disconnected.message.len = disconnected.name_len + DISCONNECTION_SUFFIX_LEN;
	if (!(disconnected.message.content = (char *)malloc(sizeof(char) * (disconnected.message.len))))
		return ;
	memcpy(disconnected.message.content,
			disconnected.name,
			disconnected.name_len);
	memcpy(disconnected.message.content + disconnected.name_len,
			DISCONNECTION_SUFFIX,
			DISCONNECTION_SUFFIX_LEN);
	c = 0;
	while (c < (*actual))
	{
		if (disconnected.sock != clients[c].sock)
			send_message(clients[c].sock, disconnected.message);
		++c;
	}
	free(disconnected.message.content);
}

/*
**		Remove the disconnecting client and update 'actual' to the new total of connected clients.
*/

void				remove_client(t_client *clients, int to_remove, int *actual)
{
	memmove(clients + to_remove, clients + to_remove + 1, (*actual - to_remove - 1) * sizeof(t_client));
	(*actual)--;
}

/*
**		Close the sockets of every clients.
*/

void				clear_clients(t_client *clients, int actual)
{
	int i;

	i = 0;
	while (i < actual)
	{
		closesocket(clients[i].sock);
		++i;
	}
}
