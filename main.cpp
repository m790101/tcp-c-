// g++ -std=c++11  main.cpp -o server
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

const char *host = "127.0.0.1";
int port = 8080;

int main()
{
    // cout << "start" << endl;
    printf("------start------\n");
    int socket0;
    struct sockaddr_in server_addr, client_addr;
    char indata[1024] = {0}, outdata[1024] = {0};

    // create socket

    // socket(int domain, int type, int protocol)

    socket0 = socket(AF_INET, SOCK_STREAM, 0);
    printf("socketResult: %d\n", socket0);

    if (socket0 == -1)
    {
        printf("socket fail");
        return 0;
    }

    // setting socket
    server_addr.sin_family = AF_INET;
    inet_aton(host, &server_addr.sin_addr);
    server_addr.sin_port = htons(port);
    printf("sin_family is %d\n", AF_INET);
    printf("server start at: %s:%d\n", inet_ntoa(server_addr.sin_addr), port);


    // bind the socket to ip and port

    // int bind(int socket, const struct sockaddr *address, socklen_t address_len);
    //   status = bind(sock_fd, (struct sockaddr *)&my_addr, sizeof(my_addr));

    bind(socket0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("\t[Info] binding...\n");
    printf("\tbind\n");

    // wait for listening

    // int listen(int socket, int backlog);

    int status = listen(socket0, 5);
    if (status == -1)
    {
        printf("listening fail");
        return 0;
    }

    printf("\t[Info] wait for connection...\n");

    //todo check if the port is using

    // client side handle

    socklen_t len = sizeof(client_addr);
    // accept server side socket
    // int accept (int socket, struct sockaddr *address,socklen_t *address_len);
    int sock_client = accept(socket0, (struct sockaddr *)&client_addr, &len);
    printf("\t[Info] Testing...\n");

    char *paddr_str = inet_ntoa(client_addr.sin_addr);
    printf("\t[Info] Receive connection from %s...\n", paddr_str);

    /* 傳送 5 個字元 */
    printf("\t[Info] Say hello back...\n");
    write(sock_client, "HELLO\n", 6);

    /* 結束 TCP 對話 */
    printf("\t[Info] Close client connection...\n");
    close(sock_client);

    /* 結束 listen 的 socket */
    printf("\t[Info] Close self connection...\n");
    close(socket0);
    return 0;

    // receive data from client
    // ssize_t recv(int socket, void *buffer, size_t length, int flags);

    // int nbytes = recv(sock_client, indata, sizeof(indata), 0);
    

    // if (nbytes == 0)
    // {
    //     printf("not data");
    //     // int shutdown(int socket, int how);
    //     close(sock_client);
    //     return 0;
    // }

    // printf("recv: %s\n", indata);

    // // send data to client
    // printf("outdata %s", outdata);
    // printf("echo %s", indata);
    // send(sock_client, outdata, strlen(outdata), 0);

    // // close socket
    // close(sock_client);
    // return 0;
}

// server side

/*
    - create socket
    - bind the socket to ip and port
    - wait for listening
    - get data from client
    - send data to client
    - close socket
*/

// client side
/*
    - create socket
    - setting connection with ip and port
    - send data
    - get data
    - close socket
*/