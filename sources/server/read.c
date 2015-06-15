#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "server.h"
#include "client.h"

/*
**		Fill buffer with BUF_SIZE bytes from the socket.
**		Disconnect the client in case of error with recv.
*/

int			read_client(SOCKET sock, char *buffer, const size_t len)
{
	int		n;

	n = 0;
	// if ((n = recv(sock, buffer, len, 0)) < 0)
	if ((n = recv(sock, buffer, len, 0)) < 0)
	{
		perror("recv()");
		n = 0;
	}
	buffer[n] = 0;
	return n;
}
