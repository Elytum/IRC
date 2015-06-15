#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "server.h"
#include "client.h"

void			client_talk(int *actual, t_client clients[MAX_CLIENTS], fd_set *rdfs, char buffer[BUF_SIZE])
{
	int			i;
	t_client	client;
	int			c;

	i = 0;
	while (i < (*actual))
	{
		/* a client is talking */
		if (FD_ISSET(clients[i].sock, rdfs))
		{
			printf("t_client [%s] talk :\n", clients[i].name);
			client = clients[i];
			c = read_client(clients[i].sock, buffer, BUF_SIZE - 1);
			/* client disconnected */
			if (c == 0)
				disconnection(actual, clients, i);
			else
			{
				printf("I = %i, buffer = [%s], len = %i\n", i, buffer, c);
				add_message(&(clients[i].message), buffer, c);
			if (S_ISREADY(clients[i].message))
			{
				send_message_to_all_clients(clients, clients[i], (*actual));
				clear_message(&(clients[i].message));
			}
		}
		break;
		}
		++i;
	}
}
