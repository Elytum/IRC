#ifndef CLIENT_H
#define CLIENT_H

#include "server.h"

#define S_IFREADY 0b00000001
#define S_ISREADY(m) (m.status & S_IFREADY)
#define S_IFERROR 0b00000010
#define S_ISERROR(m) (m.status & S_IFERROR)

#define NAME_SIZE 9

typedef struct 		s_message
{
	char			*content;
	size_t			len;
	size_t			pos;
	size_t			max;
	char			status;
}					t_message;

typedef struct
{
	SOCKET			sock;
	char			name[NAME_SIZE];
	t_message		message;
}					Client;

#endif /* guard */