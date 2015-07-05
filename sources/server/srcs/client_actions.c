#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "server.h"
#include "client.h"

/*
**		Handle client talking
**			-If he talks, add the buffer to his message
**			-If his buffer is ready to be interprated, use it
*/

void			interprate_message(t_client clients[MAX_CLIENTS], t_client *client, int *actual)
{
	if (S_ISTALK((*client)) &&
		!(client->message.len == 1 && client->message.content[0] == '\n'))
		send_message_to_all_clients(clients, *client, (*actual));
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