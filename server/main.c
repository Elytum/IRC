#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "server.h"
#include "client.h"

void     init_clients(Client clients[MAX_CLIENTS])
{
   int   i;

   i = 0;
   while (i < MAX_CLIENTS)
   {
      clients[i].message.content = NULL;
      clients[i].message.len = 0;
      clients[i].message.max = 0;
      clients[i].message.pos = 0;
      clients[i].message.status = 0;
      ++i;
   }
}

void     prepare_pool(fd_set *rdfs, Client clients[MAX_CLIENTS], const SOCKET sock, const int actual)
{
   int   i;

   i = 0;
   FD_ZERO(rdfs);

   /* add STDIN_FILENO */
   FD_SET(STDIN_FILENO, rdfs);

   /* add the connection socket */
   FD_SET(sock, rdfs);

   /* add socket of each client */
   i = 0;
   while (i < actual)
   {
      FD_SET(clients[i].sock, rdfs);
      ++i;
   }
}

void     select_pool(fd_set *rdfs, const int max)
{
   if (select(max + 1, rdfs, NULL, NULL, NULL) == -1)
   {
      perror("select()");
      exit(errno);
   }
}

int       client_disconnect(const SOCKET sock, char buffer[BUF_SIZE])
{
   /* new client */
   SOCKADDR_IN    csin = { 0 };
   socklen_t      sinsize = sizeof csin;
   int            csock = accept(sock, (SOCKADDR *)&csin, &sinsize);

   if (csock == SOCKET_ERROR)
   {
      perror("accept()");
      return (0);
   }

   /* after connecting the client sends its name */
   if (read_client(csock, buffer) == -1)
   {
      /* disconnected */
      return (0);
   }
   return (csock);
}

void        add_message(t_message *message, char buffer[BUF_SIZE], int c)
{
   char     *tmp;

   if (!(message->content))
   {
      printf("Content is null\n");
      printf("c = %i\n", c);
      if (!(message->content = (char *)malloc(sizeof(char) * (c + 1))))
      {
         perror("malloc()");
         exit(errno);
      }
      message->pos = 0;
      message->max = c + 1;
   }
   if (message->max < message->pos + c + 1)
   {
      tmp = message->content;
      if (!(message->content = (char *)malloc(sizeof(char) * (message->pos + c + 1))))
      {
         perror("malloc()");
         exit(errno);
      }
      memcpy(message->content, tmp, message->pos);
      free(tmp);
   }
   memcpy(message->content + message->pos, buffer, c);
   message->pos += c;
   message->content[message->pos] = '\0';
   if (message->pos > 0)
   {
      printf("Check 1\n");
      if (message->content[0] == '\0')
      {
         if (message->pos == message->len)
            message->status |= S_IFREADY;
         else if (message->pos > message->len)
            message->status |= S_IFERROR;
      }
      else if ((tmp = strchr(message->content, '\n')))
      {
         printf("Check 2\n");
         *tmp = '\0';
         message->len = tmp - message->content;
         message->status |= S_IFREADY;
         printf("Flag == %i\n", S_ISREADY((*message)));
      }
   }
}

void        clear_message(t_message *message)
{
   printf("Clearing [%s]\n", message->content);
   free(message->content);
   message->content = NULL;
   message->len = 0;
   message->max = 0;
   message->pos = 0;
   message->status = 0;
}

void        client_talk(int *actual, Client clients[MAX_CLIENTS], fd_set *rdfs, char buffer[BUF_SIZE])
{
   int      i;
   Client   client;
   int      c;

   printf("Client talk :\n");

   i = 0;
   while (i < (*actual))
   {
      /* a client is talking */
      if (FD_ISSET(clients[i].sock, rdfs))
      {
         client = clients[i];
         c = read_client(clients[i].sock, buffer);
         /* client disconnected */
         if (c == 0)
         {
            closesocket(clients[i].sock);
            remove_client(clients, i, actual);
            strncpy(buffer, client.name, BUF_SIZE - 1);
            strncat(buffer, " disconnected !", BUF_SIZE - strlen(buffer) - 1);
            send_message_to_all_clients(clients, client, (*actual), buffer, 1);
         }
         else
         {
            printf("I = %i, buffer = [%s], len = %i\n", i, buffer, c);
            add_message(&(clients[i].message), buffer, c);
            if (S_ISREADY(clients[i].message))
            {
               printf("True\n");
               // send_message_to_all_clients(clients, client, (*actual), buffer, 0);
               clear_message(&(clients[i].message));
            }
         }
         break;
      }
      ++i;
   }
}

static void app(void)
{
   const SOCKET   sock = init_connection();
   char           buffer[BUF_SIZE];
   int            actual = 0;
   int            max = sock;
   Client         clients[MAX_CLIENTS];
   int            csock;
   fd_set         rdfs;

   init_clients(clients);
   while (1)
   {
      prepare_pool(&rdfs, clients, sock, actual);
      select_pool(&rdfs, max);
      if (FD_ISSET(STDIN_FILENO, &rdfs)) /* stop process when type on keyboard */
         break;
      else if (FD_ISSET(sock, &rdfs))
      {
         if ((csock = client_disconnect(sock, buffer)))
         {
            /* what is the new maximum fd ? */
            max = csock > max ? csock : max;
            FD_SET(csock, &rdfs);
            Client c = { csock };
            strncpy(c.name, buffer, BUF_SIZE - 1);
            clients[actual] = c;
            actual++;
         }
      }
      else
         client_talk(&actual, clients, &rdfs, buffer);
   }

   clear_clients(clients, actual);
   end_connection(sock);
}

static void clear_clients(Client *clients, int actual)
{
   int i;

   i = 0;
   while (i < actual)
   {
      closesocket(clients[i].sock);
      ++i;
   }
}

static void remove_client(Client *clients, int to_remove, int *actual)
{
   /* we remove the client in the array */
   memmove(clients + to_remove, clients + to_remove + 1, (*actual - to_remove - 1) * sizeof(Client));
   /* number client - 1 */
   (*actual)--;
}

static void send_message_to_all_clients(Client *clients, Client sender, int actual, const char *buffer, char from_server)
{
   int i = 0;
   char message[BUF_SIZE];
   message[0] = 0;

   for(i = 0; i < actual; i++)
   {
      /* we don't send message to the sender */
      if(sender.sock != clients[i].sock)
      {
         if(from_server == 0)
         {
            strncpy(message, sender.name, BUF_SIZE - 1);
            strncat(message, " : ", sizeof message - strlen(message) - 1);
         }
         strncat(message, buffer, sizeof message - strlen(message) - 1);
         write_client(clients[i].sock, message);
      }
   }
}

static int init_connection(void)
{
   SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
   SOCKADDR_IN sin = { 0 };

   if(sock == INVALID_SOCKET)
   {
      perror("socket()");
      exit(errno);
   }

   sin.sin_addr.s_addr = htonl(INADDR_ANY);
   sin.sin_port = htons(PORT);
   sin.sin_family = AF_INET;

   if(bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
   {
      perror("bind()");
      exit(errno);
   }

   if(listen(sock, MAX_CLIENTS) == SOCKET_ERROR)
   {
      perror("listen()");
      exit(errno);
   }

   return sock;
}

static void end_connection(int sock)
{
   closesocket(sock);
}

static int read_client(SOCKET sock, char *buffer)
{
   int n = 0;

   if((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
   {
      perror("recv()");
      /* if recv error we disonnect the client */
      n = 0;
   }

   buffer[n] = 0;

   return n;
}

static void write_client(SOCKET sock, const char *buffer)
{
   if(send(sock, buffer, strlen(buffer), 0) < 0)
   {
      perror("send()");
      exit(errno);
   }
}

int main(int argc, char **argv)
{
   app();
   return EXIT_SUCCESS;
}