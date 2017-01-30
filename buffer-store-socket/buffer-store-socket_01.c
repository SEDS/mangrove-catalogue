// Juliet CWE666_Operation_on_Resource_in_Wrong_Phase_of_Lifetime__listen_bind_accept_18.c
// Original structure: buffer-store-socket

// #################################################################
// ## Variant: buffer-store-socket_01
// ## CHANGE: Limit socket message size based on buffer size alone
// #################################################################

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

#define TCP_PORT 27015
#define LISTEN_BACKLOG 5

#define SIZE 100

int main(void)
{
    char data[SIZE] = "";
    int recvResult;
    struct sockaddr_in service;
    int listenSocket = INVALID_SOCKET;
    int acceptSocket = INVALID_SOCKET;
    // 'dataLen' is assigned 0.
    size_t dataLen = strlen(data);
    do {
        listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (listenSocket == INVALID_SOCKET)
        {
            break;
        }
        memset(&service, 0, sizeof(service));
        service.sin_family = AF_INET;
        service.sin_port = htons(TCP_PORT);
        if (bind(listenSocket, (struct sockaddr*)&service, sizeof(service)) == SOCKET_ERROR)
        {
            break;
        }
        if (listen(listenSocket, LISTEN_BACKLOG) == SOCKET_ERROR)
        {
            break;
        }
        acceptSocket = accept(listenSocket, NULL, NULL);
        if (acceptSocket == SOCKET_ERROR)
        {
            break;
        }
        // Remember that 'dataLen' is 0.
        // CHANGE: Limit size of message read into memory based on the buffer size alone (ignore used space in the buffer).
        recvResult = recv(acceptSocket, (char *)data+dataLen, (int)(SIZE-1), 0);
        if (recvResult == SOCKET_ERROR || recvResult == 0)
        {
            break;
        }
        // We've established that 'recvResult' must be positive at this point (see previous conditional).
        // Also, 'recvResult' can be at most 99 (see third argument of `recv` above).
        // Thus, 'recvResult' is in the bounds [1,99], which is valid for the 'data' memory block.

        // Tool C FP: none
        // Tool B FP: none
        // Tool A FP: none
        data[recvResult] = '\0';
    } while (1);
    if (listenSocket != INVALID_SOCKET)
    {
        close(listenSocket);
    }
    if (acceptSocket != INVALID_SOCKET)
    {
        close(acceptSocket);
    }
    return 0;
}