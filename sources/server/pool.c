#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "server.h"
#include "client.h"

/*
**		Prepate the pool of sockets for the select
**			- FD_ZERO(rdfs) : add STDIN_FILENO.
**			- FD_SET(STDIN_FILENO, rdfs) : add the connection socket.
**			- FD_SET(clients[i].sock, rdfs) : add socket of each client.
*/

void		prepare_pool(fd_set *rdfs, t_client clients[MAX_CLIENTS], const SOCKET sock, const int actual)
{
	size_t	i;

	FD_ZERO(rdfs);
	FD_SET(STDIN_FILENO, rdfs);
	FD_SET(sock, rdfs);
	i = 0;
	while (i < actual)
	{
		FD_SET(clients[i].sock, rdfs);
		++i;
	}
}

/*
**		Launch select inside the pool
*/

void		select_pool(fd_set *rdfs, const int max)
{
	if (select(max + 1, rdfs, NULL, NULL, NULL) == -1)
	{
		perror("select()");
		exit(errno);
	}
}
