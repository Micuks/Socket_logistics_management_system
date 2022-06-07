#include "History.h"
#include "Menu.h"
#include "Warehouse.h"
#include <bits/stdc++.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

const int PORT = 5760;

using namespace std;

Console con;
Warehouse ware;
Menu men(&ware);

int main() {
    int servSock;
    struct sockaddr_in servAddr;
    int opt = 1;
    int servAddrLen = sizeof(servAddr);
    char buffer[1024] = {0};

    // Create socket file descriptor
    if ((servSock = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(servSock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsocketopt failed");
        exit(EXIT_FAILURE);
    }

    bzero((char *) &servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(PORT);
    servAddr.sin_addr.s_addr = INADDR_ANY;

    // Attach socket to port PORT
    if (bind(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(servSock, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in cliAddr;
    int cliAddrLen = sizeof(cliAddr);
    int cliSock;
    if ((cliSock = accept(servSock, (struct sockaddr *)&cliAddr,
                           (socklen_t *)&cliAddrLen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    int valRead = read(cliSock, buffer, 1024);
    printf("%s\n", buffer);
    char *reply = "hello from server";
    write(cliSock, reply, strlen(reply));

    printf("hello message sent from server");

    close(cliSock);
    shutdown(servSock, SHUT_RDWR);
    men.start();
    return 0;
}
