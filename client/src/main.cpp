#include "History.h"
#include "Menu.h"
#include "Warehouse.h"
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <sys/socket.h>
#include <unistd.h>

const char* SERVER_ADD = "127.0.0.1";
const int PORT = 5760;

using namespace std;

Console con;

int main() {
    int cliSock = 0, servSock;
    struct sockaddr_in servAddr;
    char buffer[1024] = {0};
    if ((cliSock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error.\n");
        exit(EXIT_FAILURE);
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(PORT);

    printf("server address is %s\n", SERVER_ADD);

    // Convert IPv4 and IPv6 address from text to binary form
    if (inet_pton(AF_INET, SERVER_ADD, &servAddr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported.\n");
        exit(EXIT_FAILURE);
    }

    // Connect to server socket
    if ((servSock = connect(cliSock, (struct sockaddr *)&servAddr,
                             sizeof(servAddr))) < 0) {
        printf("\nConnection failed.\n");
        exit(EXIT_FAILURE);
    }
    char *hello = "hello from client";
    write(cliSock, hello, strlen(hello));
    printf("message sent");
    int valread = read(cliSock, buffer, 1024);
    printf("%s\n", buffer);

    close(cliSock);
    shutdown(servSock, SHUT_RDWR);

    Warehouse ware;
    Menu men(&ware, cliSock);
    men.start();
    return 0;
}
