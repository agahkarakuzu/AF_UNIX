#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>


#define SERVER_PATH     "/tmp/rth2qmrlab"
#define BUFFER_LENGTH    1024
#define FALSE              0

// I need kinda MATLAB version of this. 

void main()
{
    int sock, msgsock, rval, rc;
    struct sockaddr_un server; // server is a structture that store addresses for UNIX domain sockets.
    char buf[BUFFER_LENGTH];

    // Create the socket here 

    // This function returns a socket descriptor, which represents an endpoint. It also identified that the UNIX
    // address family (AF_UNIX) with the stream transport (SOCK_STREAM) will be used for the socket. 

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    
    if (sock < 0)
    {
        perror("Cannot open the socket.");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    server.sun_family = AF_UNIX;
    strcpy(server.sun_path, SERVER_PATH); // This is created as a socker in the system filename space. 

    // The file should be deleted by the caller when it is no longer needed. 

    // Command in the if statement is for binding. 

    // Bind gets a unique name for the socket. 

    rc = bind(sock, (struct sockaddr *)&server, SUN_LEN(&server));

    if (rc < 0)
    {
        perror("Binding stream socket");
        exit(1);
    }

    printf("Socket has name %s\n", server.sun_path);

    // The listen function allows the server to accept incoming client connections. Here, backlog is set to 5.
    // This means that the system will que 5 incoming connection requests before the system starts rejecting incoming
    // requests. 

    rc = listen(sock, 10);
    
    if (rc<0){

        perror("Listen() failed.");
        exit(1);
    }

    for (;;) // Infinite loop 
    {
        // Accept an incoming request. This call will block indefinetely waiting for the incoming connection to arrive.

        msgsock = accept(sock, NULL, NULL);

        if (msgsock < 0)

            perror("Accept() failed.");

        else

            do
            {
                bzero(buf, sizeof(buf));
                if ((rval = read(msgsock, buf, BUFFER_LENGTH)) < 0)
                    perror("reading stream message");
                else if (rval == 0)
                    printf("Ending connection\n");
                else
                    printf("-->%s\n", buf);
            } while (rval > 0);
        close(msgsock);
    }

    close(sock);
    unlink(SERVER_PATH);
}
