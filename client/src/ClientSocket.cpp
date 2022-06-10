#include "ClientSocket.h"

ClientSocket::ClientSocket() {}

ClientSocket::ClientSocket(const char *hostName, int portNum) {
    this->setSocket(hostName, portNum);
}

void ClientSocket::setSocket(const char *hostName, int portNum) {
    if (this->setUp)
        throw std::logic_error("Socket already set");

    this->portNumber = portNum;

    int returnVal;

    addrinfo hints;
    addrinfo *serverAddressList;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    returnVal = getaddrinfo(hostName, std::to_string(portNum).c_str(), &hints,
                            &serverAddressList);

    // Check for an error with getaddrinfo()
    if (returnVal != 0) {
        throw std::runtime_error(strcat((char *)"ERROR getting host address: ",
                                        gai_strerror(returnVal)));
    }

    // Set the first host in the list to the desired host
    addrinfo serverAddress = *serverAddressList;

    this->connectionSocket =
        socket(serverAddress.ai_family, serverAddress.ai_socktype,
               serverAddress.ai_protocol);

    // Checks for errors initializing socket
    if (socket < 0)
        throw std::runtime_error(
            strcat((char *)"ERROR opening socket: ", strerror(errno)));

    if (connect(this->connectionSocket, serverAddress.ai_addr,
                serverAddress.ai_addrlen) < 0)
        throw std::runtime_error(
            strcat((char *)"ERROR connecting: ", strerror(errno)));

    freeaddrinfo(serverAddressList);

    this->setUp = true;
}

std::string ClientSocket::send(const char *message, bool ensureFullStringSent) {
    if (!this->setUp)
        throw std::logic_error("Socket not set");

    // Empty messages won't be sent
    if (std::string(message) == "") {
        message = "none";
        throw std::logic_error("No message to send");
        //        std::perror("No message to send");
    }

    unsigned long messageLength = strlen(message);

    long sentSize = write(this->connectionSocket, message, messageLength);

    if (sentSize < 0) {
        throw std::runtime_error(
            strcat((char *)"ERROR sending message: ", strerror(errno)));
    } else if (sentSize < messageLength) {
        std::string extraStr;
        for (unsigned long a = sentSize; a < messageLength; a++) {
            extraStr += message[a];
        }
        if (ensureFullStringSent) {
            this->send(extraStr.c_str(), ensureFullStringSent);
            return "";
        }
        return extraStr;
    }
    return "";
}

std::string ClientSocket::receive(bool *socketClosed) {
    if (!this->setUp)
        throw std::logic_error("Socket not set");

    // Initialize the buffer where received info is stored
    bzero(this->buffer, BUFFER_SIZE);

    long messageSize;

    messageSize = read(this->connectionSocket, this->buffer, BUFFER_SIZE);

    // Checks for errors reading from the socket
    if (messageSize < 0)
        throw std::runtime_error(
            strcat((char *)"ERROR reading from socket: ", strerror(errno)));

    if (socketClosed != nullptr && messageSize == 0) {
        *socketClosed = true;
    }

    std::string str = std::string(buffer, messageSize);

    // Check if there is more data waiting to be read, and if so, read it
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(this->connectionSocket, &readfds);
    int n = this->connectionSocket + 1;

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 20000;

    int returnValue = select(n, &readfds, NULL, NULL, &timeout);
    if (returnValue < 0) {
        throw std::runtime_error(
            std::string("ERROR finding information about socket: ") +
            std::string(strerror(errno)));
    } else if (returnValue > 0) {
        str += this->receive();
    }

    return str;
}

void ClientSocket::close() {
    if (!this->setUp)
        throw std::logic_error("Socket not set");

    ::close(this->connectionSocket);
    portNumber = 0;
    this->setUp = false;
}

void ClientSocket::setTimeout(unsigned int seconds, unsigned int milliseconds) {
    if (!this->setUp)
        throw std::logic_error("Socket not set");

    struct timeval time;
    time.tv_sec = seconds;
    time.tv_usec = (milliseconds * 1000);

    setsockopt(this->connectionSocket, SOL_SOCKET, SO_RCVTIMEO,
               (const char *)&time, sizeof(time));
}

bool ClientSocket::getSet() const { return this->setUp; }

ClientSocket::~ClientSocket() {
    if (this->setUp) {
        // Properly terminate the sockets
        try {
            ::close(this->connectionSocket);
        } catch (...) {
            printf("Error closing socket (client side)");
        }
    }
}
