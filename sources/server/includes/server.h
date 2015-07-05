#ifndef SERVER_H
#define SERVER_H

#ifdef WIN32

#include <winsock2.h>

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#endif

#define CRLF			"\r\n"
#define PORT			8080
#define MAX_CLIENTS		100

#define BUF_SIZE		9

#define SEPARATOR " : "
#define SEPARATOR_LEN (sizeof(SEPARATOR) - 1)
#define DISCONNECTION_SUFFIX " disconnected !\n"
#define DISCONNECTION_SUFFIX_LEN (sizeof(DISCONNECTION_SUFFIX) - 1)

#define EXCLUDED_CHARACTERS "\n"

#define CONNECTION_STRING "Please enter your pseudo\n"
#define PSEUDO_ERROR_NAMETOOSHORT "Name too short, minimum "
#define PSEUDO_ERROR_NAMETOOLONG "Name too long, maximum "
#define PSEUDO_ERROR_INVALIDCHARACTER "Invalid character, name can't contain ("EXCLUDED_CHARACTERS") "
#define PSEUDO_ERROR ", please retype\n"

#include "client.h"

// static int		init_connection(void);

//Messages_handling

void			send_message(SOCKET sock, const t_message message);
void			send_string(SOCKET sock, const char *message, const size_t len);
void			send_message_to_all_clients(const t_client *clients, const t_client sender, const int actual);
void				send_message_to_client(const t_client *clients, const t_client sender, const int actual, const char *target);
void			clear_message(t_message *message);
void			add_message(t_message *message, char buffer[BUF_SIZE], int c);
t_message		create_message(const char *str, size_t len);
void			message_replace(t_client *client, t_message message);
//Pool handling

void			prepare_pool(fd_set *rdfs, t_client clients[MAX_CLIENTS], const SOCKET sock, const int actual);
void			select_pool(fd_set *rdfs, const int max);

//Read handling

int				read_client(SOCKET sock, char *buffer, const size_t len);

//t_client handling

int				client_status_update(const SOCKET sock, t_client *client);
void			disconnection(int *actual, t_client clients[MAX_CLIENTS], size_t i);
void			remove_client(t_client *clients, int to_remove, int *actual);
void			clear_clients(t_client *clients, int actual);
void			client_talk(int *actual, t_client clients[MAX_CLIENTS], fd_set *rdfs, char buffer[BUF_SIZE]);
int				pseudo_error(t_client *client);
void			connection_request(t_client *client);
#endif /* guard */
