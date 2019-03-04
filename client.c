// This program connects to the socket /tmp/rth2qmrlab and sends message to that socket. 

#include <sys/types.h>
#include <sys/socket.h> 
#include <sys/un.h>
#include <stdio.h> 
#include <string.h>

#define DATA "Hello from the othersiiiiideee."

#define SERVER_PATH "/tmp/rth2qmrlab"
#define BUFFER_LENGTH 1024
#define FALSE 0 


void main(int argc, char *argv[]){

    int sd =-1, rc, bytesReceived, sock;
    char buffer[BUFFER_LENGTH];
    struct sockaddr_un server; 

    memset(&server, 0, sizeof(server));
    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    if (sock<0){
        perror("Cannot open socket.");
        exit(1);
    }

    if (argc > 1)
         strcpy(serveraddr.sun_path, argv[1]);
      else
         strcpy(serveraddr.sun_path, SERVER_PATH);

    // Establish a connection to the server. 

    rc = connect(sock, (struct sockaddr *)&server, SUN_LEN(&server));

    if (rc<0){
        perror("Connection to the server failed.");
        exit(1);
    }

    rc = write(sock, DATA, sizeof(DATA));

    if(rc < 0){
        perror("Cannot write on the stream socket.");
    }

    close(sock);
}