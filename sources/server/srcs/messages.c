#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "server.h"
#include "client.h"

/*
**		Send a t_message to every client except to the sending one.
*/

static void print_message(t_message message)
{
	write(1, "Message = [", 11);
	write(1, message.content, message.len);
	write(1, "]\n", 2);
}

void				send_message_to_all_clients(const t_client *clients,
			const t_client sender, const int actual)
{
	int				i;
	t_message		message;
	const char		separatator[] = " : ";
	const size_t	separatator_len = sizeof(separatator) - 1;

	message.len = sender.name_len + SEPARATOR_LEN + sender.message.len;
	if (!(message.content = (char *)malloc(sizeof(char) * message.len)))
		return ;
	memcpy(message.content, sender.name, sender.name_len);
	memcpy(message.content + sender.name_len, SEPARATOR, separatator_len);
	memcpy(message.content + sender.name_len + SEPARATOR_LEN, sender.message.content, sender.message.len);
print_message(message);
	i = 0;
	while (i < actual)
	{
		if (sender.sock != clients[i].sock && S_ISCONNECT(clients[i]))
			send_message(clients[i].sock, message);
		++i;
	}
	free(message.content);
}

/*
**		Write a t_message to a socket.
*/

void				send_message(SOCKET sock, const t_message message)
{
	if (send(sock, message.content, message.len, 0) < 0)
	{
		perror("send()");
		exit(errno);
	}
}

/*
**		Write a string to a socket.
*/

void				send_string(SOCKET sock, const char *message, const size_t len)
{
	if (send(sock, message, len, 0) < 0)
	{
		perror("send()");
		exit(errno);
	}
}

/*
**		Clear a t_message.
*/

void				clear_message(t_message *message)
{
	printf("Clearing [%s]\n", message->content);
	free(message->content);
	message->content = NULL;
	message->len = 0;
	message->max = 0;
	message->pos = 0;
	message->status = 0;
}
