#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <stdexcept>
#include <string>
#include <vector>

#include <cerrno>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 65535

class ServerSocket {
  public:
    ServerSocket();
    ServerSocket(int portNum, int maxConnections);
    ~ServerSocket();

    void setSocket(int portNum, int maxConnections);

    void addClient();

    void closeConnection(unsigned int clientIndex);

    std::string send(const char *message, unsigned int clientIndex,
                     bool ensureFullStringSent = false);

    std::string receive(unsigned int clientIndex, bool *socketClosed = nullptr);

    void setTimeout(unsigned int seconds, unsigned int milliseconds = 0);

    void setHostTimeout(unsigned int seconds, unsigned int milliseconds = 0);

    unsigned int numberOfClients() const;

    bool isSet() const;

  private:
    // Private properties

    int portNumber; // The port nubmer where connections are accepted

    addrinfo serverAddress;

    int hostSocketFD;

    std::vector<bool>
        activeConnections; //[MAX_NUMBER_OF_CONNECTIONS]; //Initialized as all
                           // false. True if the connection of that index is an
                           // active connection

    std::vector<int> clientSocketsFD; //[MAX_NUMBER_OF_CONNECTIONS];

    std::vector<sockaddr_storage>
        clientAddresses;                       //[MAX_NUMBER_OF_CONNECTIONS];
    std::vector<socklen_t> clientAddressSizes; //[MAX_NUMBER_OF_CONNECTIONS];

    char buffer[BUFFER_SIZE];

    bool setUp = false; // Represents if the socket has already been set. If
                        // not, reading and writing will cause errors

    int getNextAvailableIndex() const;
};

#endif
