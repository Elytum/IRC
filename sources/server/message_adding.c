#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "server.h"
#include "client.h"

/*
**				Add a buffer to a t_message, updating his status.
*/


/*
**		Allocate 'content' in case it hasn't be yet or the message is a new one.
*/

static void	new_content(t_message *message, const int c)
{
	if (!(message->content = (char *)malloc(sizeof(char) * (c + 1))))
	{
		perror("malloc()");
		exit(errno);
	}
	message->pos = 0;
	message->max = c + 1;
}

/*
**		Realloc 'content' in case it's too little to contain the new buffer.
*/

static void	realloc_content(t_message *message, const int c)
{
	char	*ptr;

	ptr = message->content;
	if (!(message->content = (char *)malloc(sizeof(char) * (message->pos + c + 1))))
	{
		perror("malloc()");
		exit(errno);
	}
	memcpy(message->content, ptr, message->pos);
	free(ptr);
}

/*
**		Update the message status.
*/

static void	update_message(t_message *message)
{
	char	*tmp;

	if (message->content[0] == '\0')
	{
		if (message->pos == message->len)
			message->status |= S_IFREADY;
		else if (message->pos > message->len)
			message->status |= S_IFERROR;
	}
	else if ((tmp = strchr(message->content, '\n')))
	{
		*tmp = '\0';
		message->len = tmp - message->content;
		message->effect = S_IFTALK;
		message->status |= S_IFREADY;
	}
}

/*
**		Main function.
*/

void		add_message(t_message *message, char buffer[BUF_SIZE], int c)
{
	if (!(message->content))
		new_content(message, c);
	if (message->max < message->pos + c + 1)
		realloc_content(message, c);
	memcpy(message->content + message->pos, buffer, c);
	message->pos += c;
	message->content[message->pos] = '\0';
	if (message->pos > 0)
		update_message(message);
}
