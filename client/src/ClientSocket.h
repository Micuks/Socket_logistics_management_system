#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <exception>
#include <iostream>
#include <string>

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 65535

class ClientSocket {
  public:
    ClientSocket();
    ClientSocket(const char *hostName, int portNum);

    ~ClientSocket();

    void setSocket(const char *hostName, int portNum);

    std::string send(const char *message, bool ensureFullStringSent = false);

    std::string receive(bool *socketClosed = nullptr);

    void close();

    void setTimeout(unsigned int seconds, unsigned int milliseconds = 0);

    bool getSet() const;

  private:
    int connectionSocket;
    int portNumber;

    char buffer[BUFFER_SIZE];

    bool setUp = false;
};

#endif
