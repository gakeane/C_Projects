
/*

*/

#include "network_utils.cpp"

#define _BUFFER_SIZE 256

int main(int argc, char* argv[]) {
  /*

  */


  // confirm enough arguments have been passed in from the command line
  if (argc < 3) {
    fprintf(stderr, "Must specify an hostname and port to connect on\n");
    exit(0);
  }

  int sockfd;                          // stores the file descriptor number for a socket
  bool quit_session = false;           // used to escape the main loop for interacting with the server

  char buffer[_BUFFER_SIZE];           // buffer to store data read from the socket
  bzero(buffer, _BUFFER_SIZE);         // Zero the data on the buffer bytes to prevent sending unwanted information


  sockfd = open_client_connection(argv[1], argv[2]);     // start a session with the server

  printf("To send a message to the server type the message and press enter\n");
  printf("To close the connection with the server type \'quit\'\n");

  // will break from this while loop if the user inputs the term quit (lowercase)
  while (!quit_session) {

    // read input from the user
    printf("prompt> ");
    fgets(buffer, _BUFFER_SIZE, stdin);

    // FIXME: Should make a utilities function for checking user quit
    // check if the user input is asking to quit
    if (strcmp(buffer, "quit\n") == 0) {
        printf("GoodBye\n");
        quit_session = true;
    }

    // FIXME: need to change this so the code will continue to read from stdin
    else if (strlen(buffer) >= _BUFFER_SIZE - 1) {
        fprintf(stderr, "WARNING: Buffer overflow, message can't be more than %u characters\n", _BUFFER_SIZE);
        quit_session = true;
    }

    // send message to server and read response
    else {
        send_message(sockfd, buffer);
        receive_message(sockfd, buffer, _BUFFER_SIZE - 1);

        printf("%s\n", buffer);

        bzero(buffer, _BUFFER_SIZE);
    }

  }// end of main loop

  close_client_connection(sockfd);
  return 0;
}
