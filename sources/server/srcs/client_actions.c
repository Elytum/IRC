#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "server.h"
#include "client.h"
#include <common.h>

/*
**		Handle client talking
**			-If he talks, add the buffer to his message
**			-If his buffer is ready to be interprated, use it
*/


t_message	get_who(t_client clients[MAX_CLIENTS], t_client *client, int actual)
{
	t_message	who;
	int	i;

	who.len = 0;
	i = 0;
	while (i < actual)
	{
		printf("Ongoint len: %zu", who.len);
		who.len += clients[i++].name_len + 1;
	}
	printf("Final len: %zu", who.len);
	if (!(who.content = (char *)malloc(sizeof(char) * who.len)))
		exit(1);
	who.len = 0;
	i = 0;
	while (i < actual)
	{
		memcpy(who.content + who.len, clients[i].name, clients[i].name_len);
		who.len += clients[i].name_len;
		who.content[who.len++] = '\n';
		++i;
	}
	printf("Received: [");
	write(1, who.content, who.len);
	printf("]\n");
	return (who);
	(void)client;
}

void			command_who(t_client clients[MAX_CLIENTS], t_client *client, int actual)
{
	char	*ptr;
	const char	error[] = "Wrong format, should be \"/who\"\n";

	ptr = client->message.content + sizeof("/who");
	while (*ptr)
	{
		if (*ptr != ' ' && *ptr != '\t' && *ptr != '\n')
		{
			send_string(client->sock, error, sizeof(error));
			return ;
		}
		++ptr;
	}
	free(client->message.content);
	client->message = get_who(clients, client, actual);
	send_message(client->sock, client->message);
	return ;
}

void			command_join(t_client *client)
{
	char	*ptr;
	char	*end;
	size_t	size;
	size_t	len;
	const char	error[] = "Wrong format, should be \"/join channel\"\n";
	const char	intro[] = "You joined the channel \"";
	const char	finish[] = "\"\n";

	// free(client->channel);
	ptr = client->message.content + sizeof("/join");
	while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n')
		ptr++;
	end = ptr;
	while (*end && *end != ' ' && *end != '\t' && *end != '\n')
		end++;
	if (*end)
		send_string(client->sock, error, sizeof(error));
	else
	{
		size = end - ptr;
		client->channel = strndup(ptr, size);
		len = sizeof(error) + size + sizeof(intro);
		if (!(ptr = (char *)malloc(sizeof(char) * sizeof(len))))
			exit(1);
		memcpy(ptr, intro, sizeof(intro));
		memcpy(ptr + sizeof(intro), client->channel, size);
		memcpy(ptr + sizeof(intro) + size, finish, sizeof(finish));
		send_string(client->sock, ptr, len);
		free(ptr);
	}
}

void			interprate_message(t_client clients[MAX_CLIENTS], t_client *client, int *actual)
{
	if (S_ISTALK((*client)) && client->message.len > 1 &&
		!(client->message.len == 1 && client->message.content[0] == '\n'))
	{
		if (client->message.content[0] == '/')
		{
			if (command_match(client->message.content + 1, "friend"))
				write(1, "friend", sizeof("friend"));
			if (command_match(client->message.content + 1, "room"))
				write(1, "room", sizeof("room"));
			else if (command_match(client->message.content + 1, "nick"))
				write(1, "nick", sizeof("nick"));
			else if (command_match(client->message.content + 1, "join"))
				command_join(client);//write(1, "join", sizeof("join"));
			else if (command_match(client->message.content + 1, "who"))
				command_who(clients, client, *actual);
			else if (command_match(client->message.content + 1, "msg"))
				write(1, "msg", sizeof("msg"));
			else
				write(1, "Command", sizeof("Command"));
		}
		else
			send_message_to_all_clients(clients, *client, (*actual));
	}
}

void			client_talk(int *actual, t_client clients[MAX_CLIENTS], fd_set *rdfs, char buffer[BUF_SIZE])
{
	int			i;
	t_client	client;
	int			c;

	i = 0;
	while (i < (*actual))
	{
		if (FD_ISSET(clients[i].sock, rdfs))
		{
			client = clients[i];
			c = read_client(clients[i].sock, buffer, BUF_SIZE - 1);
			if (c == 0)
				disconnection(actual, clients, i);
			else
			{
				add_message(&(clients[i].message), buffer, c);
				if (S_ISREADY(clients[i].message))
				{
					if (!S_ISCONNECT(clients[i]))
						connection_request(&(clients[i]));
					else
						interprate_message(clients, &(clients[i]), actual);
					clear_message(&(clients[i].message));
				}
			}
			break;
		}
		++i;
	}
}
