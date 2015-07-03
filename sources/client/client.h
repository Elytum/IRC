#ifndef CLIENT_H
#define CLIENT_H

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

#define CRLF	 "\r\n"
#define PORT	 8080

#define BUF_SIZE 1024

// static void		app(const char *address, const size_t port);
static void		app(SOCKET sock);
static int		init_connection(const char *address, const size_t port);
static void		end_connection(int sock);
// static int		read_server(SOCKET sock, char *buffer);
static int 		read_server(SOCKET sock, char **buffer);
static void		write_server(SOCKET sock, char *buffer);

#endif /* guard */