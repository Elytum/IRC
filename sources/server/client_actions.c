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

void			interprate_message(t_client clients[MAX_CLIENTS], t_client client, int *actual)
{
	if (S_ISTALK(client))
		send_message_to_all_clients(clients, client, (*actual));
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
			printf("t_client [%s] talk :\n", clients[i].name);
			client = clients[i];
			c = read_client(clients[i].sock, buffer, BUF_SIZE - 1);
			if (c == 0)
				disconnection(actual, clients, i);
			else
			{
				printf("I = %i, buffer = [%s], len = %i\n", i, buffer, c);
				add_message(&(clients[i].message), buffer, c);
				if (S_ISREADY(clients[i].message))
				{
					interprate_message(clients, clients[i], actual);
					clear_message(&(clients[i].message));
				}
			}
			break;
		}
		++i;
	}
}
