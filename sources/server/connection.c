#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "server.h"
#include "client.h"

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
	if ((client->name_len = read_client(csock, client->name, NAME_SIZE)) == -1)
		return (0);
client->name[--client->name_len] = '\0';
	client->sock = csock;
	client->message.content = NULL;
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
	if (!(disconnected.message.content = (char *)malloc(sizeof(char) * (disconnected.message.len + 1))))
		return ;
	strncpy(disconnected.message.content, disconnected.name, BUF_SIZE - 1);
	strcpy(disconnected.message.content + disconnected.name_len - 1, DISCONNECTION_SUFFIX);
	printf("Sending [%s] (len = %zu)\n", disconnected.message.content, disconnected.message.len);
	c = 0;
	while (c < (*actual))
	{
		if (disconnected.sock != clients[c].sock)
			write_message(c, disconnected.message);
		++c;
	}
	write_message(disconnected.sock, disconnected.message);
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
