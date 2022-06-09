#include "ServerSocket.h"

ServerSocket::ServerSocket() {}

ServerSocket::ServerSocket(int portNum, int maxConnections) {
    this->setSocket(portNum, maxConnections);
}

void ServerSocket::setSocket(int portNum, int maxConnections) {
    if (this->setUp)
        throw std::logic_error("Socket already set");

    int returnVal;

    for (int a = 0; a < maxConnections; a++) {
        this->activeConnections.push_back(false);
        this->clientSocketsFD.push_back(0);
        this->clientAddresses.push_back(sockaddr_storage());
        this->clientAddressSizes.push_back(socklen_t());
    }

    addrinfo hints;

    addrinfo *serverAddressList;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    returnVal = getaddrinfo(NULL, std::to_string(portNum).c_str(), &hints,
                            &serverAddressList);

    if (returnVal != 0)
        throw std::runtime_error(strcat((char *)"ERROR getting local address: ",
                                        gai_strerror(returnVal)));

    this->serverAddress = *serverAddressList;

    this->hostSocketFD =
        socket(this->serverAddress.ai_family, this->serverAddress.ai_socktype,
               this->serverAddress.ai_protocol);

    // Checks for errors initializing socket
    if (socket < 0)
        throw std::runtime_error(
            strcat((char *)"ERROR opening socket", strerror(errno)));

    int enable = 1;
    if (setsockopt(this->hostSocketFD, SOL_SOCKET, SO_REUSEADDR, &enable,
                   sizeof(int)) == -1) {
        throw std::runtime_error(
            strcat((char *)"ERROR setting port to reusable", strerror(errno)));
    }

    if (bind(this->hostSocketFD, this->serverAddress.ai_addr,
             this->serverAddress.ai_addrlen) < 0) {
        throw std::runtime_error(
            strcat((char *)"ERROR binding host socket to local port: ",
                   strerror(errno)));
    }

    if (listen(this->hostSocketFD, 1) < 0) {
        throw std::runtime_error(
            strcat((char *)"ERROR listening for incoming connections",
                   strerror(errno)));
    }

    freeaddrinfo(serverAddressList);

    this->setUp = true;
}

void ServerSocket::addClient() {
    if (!this->setUp)
        throw std::logic_error("Socket not set");

    int nextIndex = this->getNextAvailableIndex();

    if (nextIndex == -1) {
        throw std::logic_error(
            strcat((char *)"Max number of sockets: ",
                   std::to_string(this->activeConnections.size()).c_str()));
    }

    this->clientSocketsFD[nextIndex] =
        accept(this->hostSocketFD,
               (struct sockaddr *)&this->clientAddresses[nextIndex],
               &this->clientAddressSizes[nextIndex]);

    // Checks for error with accepting
    if (this->clientSocketsFD[nextIndex] < 0)
        throw std::runtime_error(
            strcat((char *)"ERROR accepting client", strerror(errno)));

    this->activeConnections[nextIndex] = true;
}

void ServerSocket::closeConnection(unsigned int clientIndex) {
    if (!this->setUp)
        throw std::logic_error("Socket not set");

    // Throw an error if there is no socket at the index to close
    if (clientIndex >= this->activeConnections.size() ||
        !this->activeConnections[clientIndex])
        throw std::logic_error("Socket index uninitialized");

    // Close the socket of the given index
    close(this->clientSocketsFD[clientIndex]);

    // Reset the information for the closed socket
    this->clientAddresses[clientIndex] = sockaddr_storage();
    this->clientAddressSizes[clientIndex] = 0;
    this->activeConnections[clientIndex] = false;
}

std::string ServerSocket::send(const char *message, unsigned int clientIndex,
                               bool ensureFullStringSent) {
    if (!this->setUp)
        throw std::logic_error("Socket not set");

    // A blank message won't be sent
    if (std::string(message) == "")
        throw std::logic_error("No message to send");

    // Throw an error if there is no socket at the index
    if (clientIndex >= this->activeConnections.size() ||
        !this->activeConnections[clientIndex])
        throw std::logic_error("Socket index uninitialized");

    unsigned long messageLength = strlen(message);

    long sentSize =
        write(this->clientSocketsFD[clientIndex], message, messageLength);

    if (sentSize < 0) {
        throw std::runtime_error(
            strcat((char *)"ERROR sending message: ", strerror(errno)));
    } else if (sentSize < messageLength) {

        std::string extraStr;
        for (unsigned long a = sentSize; a < messageLength; a++) {
            extraStr += message[a];
        }
        if (ensureFullStringSent) {

            this->send(extraStr.c_str(), clientIndex, ensureFullStringSent);

            return "";
        }
        return extraStr;
    }
    return "";
}

std::string ServerSocket::receive(unsigned int clientIndex,
                                  bool *socketClosed) {
    if (!this->setUp)
        throw std::logic_error("Socket not set");

    if (clientIndex >= this->activeConnections.size() ||
        !this->activeConnections[clientIndex])
        throw std::logic_error("Socket index uninitialized");

    // Initialize the buffer where received info is stored
    bzero(this->buffer, BUFFER_SIZE);

    long messageSize;

    messageSize =
        read(this->clientSocketsFD[clientIndex], this->buffer, BUFFER_SIZE);

    // Checks for errors reading from the socket
    if (messageSize < 0)
        throw std::runtime_error(
            strcat((char *)"ERROR reading from socket: ", strerror(errno)));

    if (socketClosed != nullptr && messageSize == 0) {
        *socketClosed = true;
        this->closeConnection(clientIndex);
    }

    std::string str = std::string(buffer, messageSize);

    // Check if there is more data waiting to be read, and if so, read it
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(this->hostSocketFD, &readfds);
    int n = this->hostSocketFD + 1;

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 20000;

    int returnValue = select(n, &readfds, NULL, NULL, &timeout);
    if (returnValue < 0) {
        throw std::runtime_error(
            std::string("ERROR finding information about socket: ") +
            std::string(strerror(errno)));
    } else if (returnValue > 0) {
        str += this->receive(clientIndex);
    }

    return str;
}

void ServerSocket::setTimeout(unsigned int seconds, unsigned int milliseconds) {
    if (!this->setUp)
        throw std::logic_error("Socket not set");

    struct timeval time; // Time holds the maximum time to wait
    time.tv_sec = seconds;
    time.tv_usec = (milliseconds * 1000);

    for (int a = 0; a < this->activeConnections.size(); a++) {
        if (this->activeConnections[a])
            setsockopt(this->clientSocketsFD[a], SOL_SOCKET, SO_RCVTIMEO,
                       (struct timeval *)&time, sizeof(struct timeval));
    }
}

void ServerSocket::setHostTimeout(unsigned int seconds,
                                  unsigned int milliseconds) {
    if (!this->setUp)
        throw std::logic_error("Socket not set");

#if defined(_WIN32)
    DWORD timeout = (seconds * 1000) + milliseconds;
    setsockopt(this->hostSocketFD, SOL_SOCKET, SO_RCVTIMEO,
               (const char *)&timeout, sizeof(timeout));
#else
    struct timeval time;
    time.tv_sec = seconds;
    time.tv_usec = (milliseconds * 1000);
    setsockopt(this->hostSocketFD, SOL_SOCKET, SO_RCVTIMEO,
               (struct timeval *)&time, sizeof(struct timeval));
#endif
}

unsigned int ServerSocket::numberOfClients() const {
    if (!this->setUp)
        throw std::logic_error("Socket not set");

    // Count the number of connections which are active
    int connections = 0;
    for (int a = 0; a < this->activeConnections.size(); a++) {
        if (this->activeConnections[a]) {
            connections++;
        }
    }
    return connections;
}

bool ServerSocket::isSet() const { return this->setUp; }

int ServerSocket::getNextAvailableIndex() const {
    if (!this->setUp)
        throw std::logic_error("Socket not set");

    for (int a = 0; a < this->activeConnections.size(); a++) {
        if (!this->activeConnections[a])
            return a;
    }
    return -1;
}

ServerSocket::~ServerSocket() {
    if (this->setUp) {
        // Properly terminate the sockets on both client and host side
        for (int clientIndex = 0; clientIndex < this->activeConnections.size();
             clientIndex++) {
            if (this->activeConnections[clientIndex]) {
                try {
                    close(this->clientSocketsFD[clientIndex]);
                } catch (...) {
                    printf("Error closing client socket (server side)");
                }
            }
        }
        try {
            close(this->hostSocketFD);
        } catch (...) {
            printf("Error closing host server socket (server side)");
        }
    }
}
