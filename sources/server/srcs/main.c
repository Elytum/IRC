#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "server.h"
#include "client.h"

static int			init_connection(void)
{
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sin;
	bzero(&sin, sizeof(SOCKADDR_IN));

	if (sock == INVALID_SOCKET)
	{
		perror("socket()");
		exit(errno);
	}

	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(PORT);
	sin.sin_family = AF_INET;

	if (bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
	{
		perror("bind()");
		exit(errno);
	}
	if (listen(sock, MAX_CLIENTS) == SOCKET_ERROR)
	{
		perror("listen()");
		exit(errno);
	}
	return (sock);
}

static int			irc_loop(t_client clients[MAX_CLIENTS], const SOCKET sock)
{
	int				actual;
	int				max;
	char			buffer[BUF_SIZE];
	fd_set			rdfs;
	int				csock;

	actual = 0;
	max = sock;
	while (42)
	{
		prepare_pool(&rdfs, clients, sock, actual);
		select_pool(&rdfs, max);
		if (FD_ISSET(STDIN_FILENO, &rdfs))
			break;
		else if (!FD_ISSET(sock, &rdfs))
			client_talk(&actual, clients, &rdfs, buffer);
		else if ((csock = client_status_update(sock, &(clients[actual]))))
		{
			max = csock > max ? csock : max;
			FD_SET(csock, &rdfs);
			++actual;
		}
	}
	return (actual);
}

void				init_clients(t_client clients[MAX_CLIENTS])
{
	// int i;

	memset((void *)clients, sizeof(t_client) * MAX_CLIENTS, 0);
	// i = 0;
	// while (i < MAX_CLIENTS)
	// 	clients[i++].channel = NULL;
}

int					main(int argc, char **argv)
{
	const SOCKET	sock = init_connection();
	int				actual;
	t_client		clients[MAX_CLIENTS];

	init_clients(clients);
	actual = irc_loop(clients, sock);
	clear_clients(clients, actual);
	closesocket(sock);
	return (EXIT_SUCCESS);
	(void)argc;
	(void)argv;
}
