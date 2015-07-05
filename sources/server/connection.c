#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "server.h"
#include "client.h"
#include <common.h>

void				connection_request(t_client *client)
{
	client->name_len = client->message.len;
	memcpy(client->name, client->message.content, client->name_len);
	client->name[--client->name_len] = '\0';
	if (!pseudo_error(client))
	{
		printf("User '%s' just connected\n", client->name);
		client->status |= S_IFCONNECT;
	}
	printf("Init pseudo = [%s]\n", client->name);
}

/*
**		Determine if the client is connecting or disconnecting and in case of connection, add it.
*/

int					client_status_update(const SOCKET sock, char buffer[BUF_SIZE], t_client *client)
{
	SOCKADDR_IN		csin = { 0 };
	socklen_t		sinsize = sizeof (csin);
	int				csock = accept(sock, (SOCKADDR *)&csin, &sinsize);
	size_t			len;

	if (csock == SOCKET_ERROR)
	{
		perror("accept()");
		return (0);
	}
	client->sock = csock;
	client->message.content = NULL;
	client->message.len = 0;
	client->status = 0;
	send_string(client->sock, CONNECTION_STRING, sizeof(CONNECTION_STRING));
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
	disconnected.message.len = ANSI_COLOR_RED_LEN + disconnected.name_len + DISCONNECTION_SUFFIX_LEN + ANSI_COLOR_RESET_LEN;
	if (!(disconnected.message.content = (char *)malloc(sizeof(char) * (disconnected.message.len))))
		return ;
	memcpy(disconnected.message.content,
			ANSI_COLOR_RED,
			ANSI_COLOR_RED_LEN);
	memcpy(disconnected.message.content + ANSI_COLOR_RED_LEN,
			disconnected.name,
			disconnected.name_len);
	memcpy(disconnected.message.content + ANSI_COLOR_RED_LEN + disconnected.name_len,
			DISCONNECTION_SUFFIX,
			DISCONNECTION_SUFFIX_LEN);
	memcpy(disconnected.message.content + ANSI_COLOR_RED_LEN + disconnected.name_len + DISCONNECTION_SUFFIX_LEN,
			ANSI_COLOR_RESET,
			ANSI_COLOR_RESET_LEN);

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
