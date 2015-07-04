#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "client.h"
#include <inputs.h>

static int  command_match(const char *str, const char *command)
{
   while (*command && *command == *str)
   {
      command++;
      str++;
   }
   return (!*command && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\0'));
}

static void app(SOCKET sock)
{
   // char buffer[BUF_SIZE];
   char  *buffer;
   fd_set rdfs;

   while(1)
   {
      FD_ZERO(&rdfs);

      /* add STDIN_FILENO */
      FD_SET(STDIN_FILENO, &rdfs);

      /* add the socket */
      FD_SET(sock, &rdfs);

      if(select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
      {
         perror("select()");
         exit(errno);
      }

      if (FD_ISSET(STDIN_FILENO, &rdfs))
      {
         if ((buffer = ft_dynamic_get("> ")))
         {
            write_server(sock, buffer);
            free(buffer);
         }
      }
      else if(FD_ISSET(sock, &rdfs))
      {
         ft_dynamic_clean();
         int n = read_server(sock, &buffer);
         /* server down */
         if (n == 0)
         {
            printf("Server disconnected !\n");
            break;
         }
         else if (n != -1)
            write(1, buffer, n);
         ft_dynamic_restore();
      }
   }

   end_connection(sock);
}

static int init_connection(const char *address, const size_t port)
{
   SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
   SOCKADDR_IN sin = { 0 };
   struct hostent *hostinfo;

   if(sock == INVALID_SOCKET)
   {
      perror("socket()");
      exit(errno);
   }

   hostinfo = gethostbyname(address);
   if (hostinfo == NULL)
   {
      printf("Unknown host %s.\n", address);
      exit(EXIT_FAILURE);
   }

   sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
   sin.sin_port = htons(port);
   sin.sin_family = AF_INET;

   if (connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
   {
      perror("connect()");
      exit(errno);
   }

   return sock;
}

static int init_connection_safe(const char *address, const size_t port)
{
   SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
   SOCKADDR_IN sin = { 0 };
   struct hostent *hostinfo;

   if (sock == INVALID_SOCKET)
   {
      printf("Invalid socket\n");
      return (sock);
   }

   hostinfo = gethostbyname(address);
   if (hostinfo == NULL)
   {
      printf("Unknown host %s.\n", address);
      return (INVALID_SOCKET);
   }

   sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
   sin.sin_port = htons(port);
   sin.sin_family = AF_INET;

   if (connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
   {
      printf("Connect error\n");
      return (INVALID_SOCKET);
   }

   return sock;
}

static void end_connection(int sock)
{
   closesocket(sock);
}

/**/
                                          // void  dumpString(char *str, size_t len) {
                                          //    while (len--) {
                                          //       // ft_putnbr(*str++);
                                          //       write(1, str++, 1);
                                          //       if (len)
                                          //          write(1, " ", 1);
                                          //       else
                                          //          write(1, "\n", 1);
                                          //    }
                                          // }
/**/

static int read_server(SOCKET sock, char **buffer)
{
   int   n = BUF_SIZE - 1;
   int   total = 0; 
   char  *tmp;
   char  buf[n];

   *buffer = NULL;
   while (n == BUF_SIZE - 1)
   {
      if ((n = recv(sock, buf, BUF_SIZE - 1, 0)) < 0)
      {
         perror("recv()");
         exit(errno);
      }
      if (!(tmp = (char *)malloc(sizeof(char) * total + n)))
         exit(1);
      memcpy(tmp, *buffer, total);
      memcpy(tmp + total, buf, n);
      free(*buffer);
      *buffer = tmp;
      total += n;
      if (total > 1 && (*buffer)[0] != '\0' && (
         (*buffer)[total - 1] == '\n' || (*buffer)[total - 1] == '\0'))
         break ;
   }
   return total;
}

static void write_server(SOCKET sock, char *buffer)
{
   size_t len;
   char     *tmp;

   if ((len = strlen(buffer)))
   {
      if (!(tmp = (char *)malloc(sizeof(char) * len + 1)))
         exit (1);
      memcpy(tmp, buffer, len);
      tmp[len] = '\n';
      if (send(sock, tmp, len + 1, 0) < 0)
      {
         free(tmp);
         perror("send()");
         exit(errno);
      }
      free(tmp);
   }
}

int main(int argc, char **argv)
{
   char  *machine;
   int   port;
   char  *buffer;
   SOCKET sock;

   if (argc == 1)
   {
      printf("Please connect to a server:\n");
      while (42)
      {
         buffer = ft_get_inputs("> ");
         if (buffer[0] == '/')
         {
            if (command_match(buffer + 1, "nick") ||
               command_match(buffer + 1, "join") ||
               command_match(buffer + 1, "leave") ||
               command_match(buffer + 1, "who") ||
               command_match(buffer + 1, "msg"))
               printf ("Can't execute this command yet, you're not connected.\n");
            else if (command_match(buffer + 1, "connect"))
            {
               char      *ptr;
               size_t   len;

               ptr = buffer + 9;
               while (*ptr == ' ' | *ptr == '\t')
                  ptr++;
               machine = ptr;
               while (*ptr && *ptr != ' ' && *ptr != '\t')
                  ptr++;
               len = ptr - machine;
               while (*ptr == ' ' || *ptr == '\t')
                  ptr++;
               if (*ptr >= '0' && *ptr <= '9')
               {
                  port = atoi(ptr);
                  while (*ptr >= '0' && *ptr <= '9')
                     ptr++;
                  if (!*ptr)
                  {
                     machine = strndup(machine, len);
                     sock = init_connection_safe(machine, port);
                     if (sock != INVALID_SOCKET)
                     {
                        app(sock);
                        break ;
                     }
                  }
                  else if (*ptr != '\0')
                     printf("Wrong format, should be \"/connect <address> <port>\".\n");
                  else
                     printf("Wrong format, port must be a number.\n");
               }
            }
            else
               printf ("Unknown command.\n");
         }
         else
            printf("You must be connected to say anything !\n");
         free(buffer);
      }
      free(buffer);
   }
   else if (argc == 3)
      app(init_connection(argv[1], atoi(argv[2])));
   else
   {
      if (argc > 3)
         printf("Usage : %s [address] [port]\n", argv[0]);
      else
         printf("Usage : %s\n", argv[0]);
      return EXIT_FAILURE;
   }
   return EXIT_SUCCESS;
}