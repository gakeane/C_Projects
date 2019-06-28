
/*

*/

#include "network_utils.cpp"

#define _BUFFER_SIZE 256
#define _CONNECTION_QUEUE 5


int main(int argc, char* argv[]) {
  /*

  */

  int listen_sockfd;                            // stores the file descriptor number for th listening socket
  int accept_sockfd;                            // stores the file descriptor for the sockets that accept a client
  bool quit_session = false;                    // used to escape the main server loop

  char buffer[_BUFFER_SIZE];                    // buffer to store data read/written from/to the socket
  bzero(buffer, _BUFFER_SIZE);                  // Zero the data on the buffer bytes to prevent sending unwanted information

  struct sockaddr_in cli_addr = {0};	          // Structure that will contain an internet address for the client
  socklen_t clilen = sizeof(cli_addr);          // datatype for storing the size of an address structure in bytes (actually an unsigned short)

  // Set the server to listen on specified port
  listen_sockfd = open_server_connection(argv[1], _CONNECTION_QUEUE);


  while(!quit_session) {

  // accept an incoming connection, note we can set the last to arguments as NULL if we don't care about the client address
    accept_sockfd = accept(listen_sockfd, (struct sockaddr *) &cli_addr, &clilen);
    char* ip = get_ip_address(&cli_addr);
    printf("Accepted new connection from %s\n", ip);

    int pid = fork();
    while(receive_message(accept_sockfd, buffer, _BUFFER_SIZE - 1)) {
        char recv_message[] = "message received";
        send_message(accept_sockfd, recv_message);
    }

    close_server_connection(accept_sockfd);
  }

  close_server_connection(listen_sockfd);
  return 0;
}
