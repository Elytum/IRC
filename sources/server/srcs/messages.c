#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "server.h"
#include "client.h"
#include <common.h>
#include <libft.h>

/*
**		Send a t_message to every client except the sending one.
*/

static void print_message(t_message message)
{
	write(1, "Message = [", 11);
	write(1, message.content, message.len);
	write(1, "]\n", 2);
}

t_message			create_message(const char *str, size_t len)
{
	t_message	message;

	if (!(message.content = (char *)malloc(sizeof(char) * len)))
		exit(1);
	memcpy(message.content, str, len);
	message.len = len;
	return (message);
}

void				message_replace(t_client *client, t_message message)
{
	free(client->message.content);
	client->message = message;
}

void				send_neutral(t_message message, const t_client *clients,
			const t_client sender, const int actual)
{
	int				i;

	i = 0;
	while (i < actual)
	{
		if (sender.sock != clients[i].sock && S_ISCONNECT(clients[i]) &&
			ft_strmatch(sender.channel, clients[i].channel))
			send_message(clients[i].sock, message);
		++i;
	}
}

void				send_allies(t_message message, const t_client *clients,
			const t_client sender, const int actual)
{
	int				i;

	if (ANSI_COLOR_BLUE_LEN == ANSI_COLOR_GREEN_LEN)
	{
		memcpy(message.content,
		ANSI_COLOR_GREEN,
		ANSI_COLOR_GREEN_LEN);
	}
	i = 0;
	while (i < actual)
	{
		if (sender.sock != clients[i].sock && S_ISCONNECT(clients[i]) &&
			ft_strmatch(sender.channel, clients[i].channel))
			send_message(clients[i].sock, message);
		++i;
	}
}

void				send_enemies(t_message message, const t_client *clients,
			const t_client sender, const int actual)
{
	int				i;

	if (ANSI_COLOR_BLUE_LEN == ANSI_COLOR_RED_LEN)
	{
		memcpy(message.content,
		ANSI_COLOR_RED,
		ANSI_COLOR_RED_LEN);
	}
	i = 0;
	while (i < actual)
	{
		if (sender.sock != clients[i].sock && S_ISCONNECT(clients[i]) &&
			ft_strmatch(sender.channel, clients[i].channel))
			send_message(clients[i].sock, message);
		++i;
	}
}

t_message			prepare_neutral_message(const t_client sender)
{
	t_message		message;
	const char		separatator[] = " : ";
	const size_t	separatator_len = sizeof(separatator) - 1;

	message.len = ANSI_COLOR_BLUE_LEN + sender.name_len +
	separatator_len + ANSI_COLOR_RESET_LEN + sender.message.len;
	if (!(message.content = (char *)malloc(sizeof(char) * message.len)))
		exit(1);
	memcpy(message.content,
			ANSI_COLOR_BLUE,
			ANSI_COLOR_BLUE_LEN);
	memcpy(message.content + ANSI_COLOR_BLUE_LEN,
			sender.name,
			sender.name_len);
	memcpy(message.content + ANSI_COLOR_BLUE_LEN + sender.name_len,
			SEPARATOR,
			separatator_len);
	memcpy(message.content + ANSI_COLOR_BLUE_LEN + sender.name_len + SEPARATOR_LEN,
			ANSI_COLOR_RESET,
			ANSI_COLOR_RESET_LEN);
	memcpy(message.content + ANSI_COLOR_BLUE_LEN + sender.name_len +
		SEPARATOR_LEN + ANSI_COLOR_RESET_LEN,
			sender.message.content,
			sender.message.len);
	return (message);
}

void				send_message_to_all_clients(const t_client *clients,
			const t_client sender, const int actual)
{
	t_message		message;

	message = prepare_neutral_message(sender);
	send_neutral(message, clients, sender, actual);
	print_message(message);
	send_allies(message, clients, sender, actual);
	send_enemies(message, clients, sender, actual);
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
