#ifndef CLIENT_H
#define CLIENT_H

#include "server.h"

#define S_IFREADY 0b00000001
#define S_ISREADY(m) (m.status & S_IFREADY)
#define S_IFERROR 0b00000010
#define S_ISERROR(m) (m.status & S_IFERROR)

#define S_IFCONNECT 0b00000001
#define S_ISCONNECT(c) (c.status & S_IFCONNECT)

#define S_IFTALK 0
#define S_ISTALK(c) (c.message.effect == S_IFTALK)

#define NAME_SIZE 9
#define NAME_MIN_SIZE 5

typedef struct 		s_message
{
	char			*content;
	size_t			len;
	size_t			pos;
	size_t			max;
	char			status;
	char			effect;
}					t_message;

typedef struct		s_client
{
	SOCKET			sock;
	char			name[NAME_SIZE];
	size_t			name_len;
	size_t			status;
	t_message		message;
}					t_client;

#endif /* guard */
