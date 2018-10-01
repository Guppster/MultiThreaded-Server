#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <err.h>

#define MAX_MSG_SIZE 1024

/*
 * The function get_sockaddr converts the server's address and port into a form usable to create a 
 * scoket
*/
struct addrinfo* get_sockaddr(const char* hostname, const char *port)
{

  struct addrinfo hints;
  struct addrinfo* results;
  int rv;

  memset(&hints, 0, sizeof(struct addrinfo));

  hints.ai_family = AF_INET;          //Return socket address for the server's IPv4 addresses
  hints.ai_socktype = SOCK_STREAM;    //Return TCP socket addresses

  /* Use getaddrinfo will get address information for the host specified by hostnae */

  rv = getaddrinfo(hostname, port, &hints, &results);
  if (rv != 0){
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    exit(1);
  }

  return results;
}

/*
 * The function open_connection establishes a connection to the server
*/
int open_connection(struct addrinfo* addr_list)
{

  struct addrinfo* p;
  int sockfd;
  //Iterate through each addr info in the list; Stop when we successully connect to one

  for (p = addr_list; p != NULL; p = p->ai_next)
  {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

        // Try the next address since the socket operation failed
       if (sockfd == -1) continue;

        //Stop iterating of we are able to connect to the server
 
       if (connect(sockfd,p->ai_addr, p->ai_addrlen) != -1) break;
  }

  freeaddrinfo(addr_list);
  
  if (p == NULL)
   err(EXIT_FAILURE, "%s", "Unable to connect");
   else
     return sockfd;

}

int main(int argc, char *argv[])
{

    int numbytes;
    char sendBuff[MAX_MSG_SIZE];
    char recvBuff[MAX_MSG_SIZE];
    struct sockaddr_in serv_addr; 
    struct hostent *server;
    int rv;
    int sum;

    if(argc != 4)
    {
        printf("\n Usage: %s hostname port number_to_be_multiplied\n",argv[0]);
        return 1;
    } 
  
    struct addrinfo* results = get_sockaddr(argv[1], argv[2]);
    int sockfd = open_connection(results);

    memset(sendBuff, '0',sizeof(sendBuff));
    memset(recvBuff, '0',sizeof(recvBuff));

    snprintf(sendBuff, sizeof(sendBuff), "%d", atoi(argv[3]));
    write(sockfd, sendBuff, strlen(sendBuff)); 

    numbytes = recv(sockfd,recvBuff,sizeof(recvBuff)-1,0);
    if (numbytes == -1){
      perror("recv");
      exit(1);
    }
  
    recvBuff[numbytes] = '\0';
    sscanf(recvBuff, "%d", &sum);
    printf("Result is %d\n", sum);
    
    return 0;
}
