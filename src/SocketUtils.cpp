#include "SocketUtils.hpp"
#include <iostream>
#include <stdexcept>
#include <netdb.h>
#include <cstring>
#include <unistd.h>

struct addrinfo* resolveAddress(const std::string& port) {
    struct addrinfo hints{};
    hints.ai_family = AF_UNSPEC;        // Support IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;    // TCP
    hints.ai_flags = AI_PASSIVE;        // For server: bind to all interfaces

    struct addrinfo* res;
    int status = getaddrinfo(nullptr, port.c_str(), &hints, &res);
    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << "\n";
        exit(1);
    }

    return res;
}


int createSocket(int family, int type, int protocol) {
    int sockfd = socket(family, type, protocol);
    if (sockfd == -1) {
        std::cerr << "socket error: " << strerror(errno) << "\n";
        exit(1);
    }

    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        std::cerr << "setsockopt error: " << strerror(errno) << "\n";
        close(sockfd);
        exit(1);
    }

    return sockfd;
}

void bindSocket(int sockfd, struct addrinfo* addressinfo) {
    if (bind(sockfd, addressinfo->ai_addr, addressinfo->ai_addrlen) == -1) {
        std::cerr << "bind error: " << strerror(errno) << "\n";
        close(sockfd);
        exit(1);
    }
}

void listenOnSocket(int sockfd, int backlog) {
    if (listen(sockfd, backlog) == -1) {
        std::cerr << "listen error: " << strerror(errno) << "\n";
        close(sockfd);
        exit(1);
    }
}

