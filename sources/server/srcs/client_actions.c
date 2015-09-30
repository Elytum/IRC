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
		who.len += clients[i++].name_len + 1;
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
	write(1, who.content, who.len);
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

void			command_join(t_client clients[MAX_CLIENTS], t_client *client, int actual)
{
	char	*ptr;
	char	*end;
	size_t	size;
	size_t	len;
	const char	error[] = "Wrong format, should be \"/join channel\".\n";
	const char	intro[] = "You joined the channel \"";
	const char	finish[] = "\".\n";
	const char	joined[] = " has joined the channel.\n";

	ptr = client->message.content + sizeof("/join");
	while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n')
		ptr++;
	end = ptr;
	while (*end && *end != ' ' && *end != '\t' && *end != '\n')
		end++;
	size = end - ptr;
	while (*end == ' ' || *end == '\t' || *end == '\n')
		end++;
	if (!*ptr || *end)
		send_string(client->sock, error, sizeof(error));
	else
	{
		// free(client->channel);
		char		*p;

		p = strndup(ptr, size);
		// client->channel = strndup(ptr, size);
		len = sizeof(error) + size + sizeof(intro);
		if (!(ptr = (char *)malloc(sizeof(char) * len)))
			exit(1);
		memcpy(ptr, intro, sizeof(intro) - 1);
		memcpy(ptr + sizeof(intro) - 1, p, size);
		memcpy(ptr + sizeof(intro) - 1 + size, finish, sizeof(finish) - 1);
		send_string(client->sock, ptr, len);

		push_allocated_chained_string(&(client->channels), p);	
		// free(ptr);

		size_t len;

		len = client->name_len + sizeof(joined) - 1;
		if (!(ptr = (char *)malloc(sizeof(char) * len)))
			exit (1);
		memcpy(ptr, client->name, client->name_len);
		memcpy(ptr + client->name_len, joined, sizeof(joined) - 1);
		message_replace(client, create_message(ptr, len));
		free(ptr);
		send_message_to_all_clients(clients, *client, actual);
	}
}

void			command_msg(t_client clients[MAX_CLIENTS], t_client *client, int actual)
{
	char	*target;
	char	*msg;

	const char	error[] = "Wrong format, should be \"/msg target\".\n";

	target = client->message.content + sizeof("/msg");
	while (*target == ' ' || *target == '\t' || *target == '\n')
		target++;
	msg = target;
	while (*msg && *msg != ' ' && *msg != '\t' && *msg != '\n')
		msg++;
	while (*msg == ' ' || *msg == '\t' || *msg == '\n')
		msg++;
	if (!*target || !*msg)
		send_string(client->sock, error, sizeof(error));
	else
	{
		char *tmp;

		tmp = client->message.content;
		msg[-1] = '\0';
		client->message.content = msg;
		printf("Sending = [%s] to [%s]\n", msg, target);
		send_message_to_client(clients, *client, actual, target);
		client->message.content = tmp;
// free(tmp);
		// client->message.content = NULL;
		// client->message.len = 0;
	}
}

void			interprate_message(t_client clients[MAX_CLIENTS], t_client *client, int *actual)
{
	char	unknown[] = "Unknown command.\n";

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
				command_join(clients, client, *actual);
			else if (command_match(client->message.content + 1, "who"))
				command_who(clients, client, *actual);
			else if (command_match(client->message.content + 1, "msg"))
				command_msg(clients, client, *actual);//write(1, "msg", sizeof("msg"));
			else
				send_string(client->sock, unknown, sizeof(unknown) - 1);
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
