
/*

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

/*
DECLARATIONS
*/

int open_client_connection(const char* hostname, const char* port);
int open_server_connection(const char* port);

void close_client_connection(int sockfd);
void close_server_connection(int sockfd);

int send_message(int sockfd, char* msg_buffer);
int receive_message(int sockfd, char* msg_buffer, int buffer_size);

void error(const char* msg);

char* get_ip_address(struct sockaddr_in* addr);

/*
DEFINITIONS
*/

int open_client_connection(const char* hostname, const char* port) {
    /* FUNCTION use to create a TCP socket connection from a client to a server

    hostname: hostname or IP address of the server to connect to
    port:     The number of the port to connect to on the server

    return:   File descriptor identifier for the socket
    */

    struct addrinfo* addrs;               // linked list of internet addresses (list of addrinfo structures)
    struct addrinfo hints = {0};          // an addrinfo structure which provides hints as to what the connection type should be like


    hints.ai_family = AF_INET;            // expected address family
    hints.ai_socktype = SOCK_STREAM;      // expected socket type
    hints.ai_protocol = IPPROTO_TCP;      // expected transport protocol

    // get server address info from DNS
    int status = getaddrinfo(hostname, port, &hints, &addrs);
    if (status != 0) {
      fprintf(stderr, "%s: %s\n", hostname, gai_strerror(status));      // gai_stderror returns a error string givne the integer returned from getaddrinfo() or getnameinfo()
      exit(1);
    }

    // create socket file
    int sockfd = socket(addrs->ai_family, addrs->ai_socktype, addrs->ai_protocol);
    if (sockfd < 0) {
      const char msg[] = "ERROR: Can't open socket";
  		error(msg);
    }

    // connect socket file to server
    int connect_status = connect(sockfd, addrs->ai_addr, addrs->ai_addrlen);
    if (connect_status < 0) {
      const char msg[] = "ERROR: Connection failed";
  		error(msg);
    }

    freeaddrinfo(addrs);            // free the memory dynamically allocated for the linked list of addrinfo structures
    return sockfd;                  // return the reference to the socket file descriptor which has been connected
  }


int open_server_connection(const char* port, int max_connections) {
  /* Sets up a socket for a server and starts it listening on the specified port
  Once the server is listening we can use accepts which will create a new socket to handle I/O with the client
  The original socket will continue to listen for connections

  port:            The port the server will listen on
  max_connections: The number of connections that the server will accept (Queue) at any one time

  return:          File descriptor identifier for the socket
  */

  struct sockaddr_in serv_addr = {0}; 	     // Structure contains an internet address for the server

  serv_addr.sin_family = AF_INET;		         // Set to AF_INET for internet addressing
	serv_addr.sin_port = htons(atoi(port));	   // htons converts the port number from host byte order (little endian) to network byte order (big endian)
	serv_addr.sin_addr.s_addr = INADDR_ANY;    // INADDR_ANY sets the address to the address the server is running on (i.e. localhost)

  // create a socket for the server
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    char msg[] = {"ERROR: Can't open socket"};
    error(msg);
  }

  // bind the socket to the specified port
  int bind_check = bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
  if (bind_check < 0) {
    char msg[] = {"ERROR: Can't bind socket"};
		error(msg);
  }

  // set the socket to listen for incomming connections
  // if there are more than max_connections that have not been accepted, the rest will be dropped
  listen(sockfd, max_connections);

  return sockfd;
}


  // FIXME: I think both functions should send a shutdown signal, wait to read 0 of the buffer, then close the socket
void close_client_connection(int sockfd) {
    /* FUNCTION cleanly terminates a session on the client side and then closes the socket

    sockfd: File descriptor identifier for the socket to be closed
    */

    close(sockfd);
  }


void close_server_connection(int sockfd) {
    /* FUNCTION cleanly terminates a session on the server side and then closes the socket

    sockfd: File descriptor identifier for the socket to be closed
    */

    close(sockfd);
}


int send_message(int sockfd, char* msg_buffer) {
  /* Writes a message to a socket and checks no errors occured

  sockfd:     File descriptor identifier for the socket to sned message to
  msg_buffer: The message to be sent

  return:     Number of bytes sent
  */

  int n = send(sockfd, msg_buffer, strlen(msg_buffer), 0);

  if (n < 0) {
    char msg[] = {"ERROR: Failed writing to socket"};
		error(msg);
  }

  return n;
}


int receive_message(int sockfd, char* msg_buffer, int buffer_size) {
  /* Reads a message from a socket and checks no errors occured

  sockfd:     File descriptor identifier for the socket to read message from
  msg_buffer: Array buffer will be stored in

  return:     Number of bytes read
  */

  bzero(msg_buffer, buffer_size);
  int n = recv(sockfd, msg_buffer, buffer_size, 0);

  if (n < 0) {
    char msg[] = {"ERROR: Failed reading from socket"};
		error(msg);
  }

  return n;
}


char* get_ip_address(struct sockaddr_in* addr) {
  /* Gets the IP address from a sockaddr_in stracture

  addr:   Address structure containin information about an internet device

  return: IP address of the server (7 bytes, 4 bytes of sin_addr separated by dots)
  */

  return inet_ntoa(addr->sin_addr);
}


void error(const char* msg) {
	/* Prints an error message fallowed by the error message thrown by the last system call to fail
  The program then terminates

  msg: Message to be printed before the system call error
  */

	perror(msg);		// from stdio
	exit(1);		    // from stdio
}
