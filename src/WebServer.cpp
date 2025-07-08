#include "WebServer.hpp"
#include "SocketUtils.hpp"
#include "HttpUtils.hpp"
#include <iostream>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>

WebServer::WebServer(const std::string &port)
{ // Constructor for web server
    port_ = port;
    server_fd_ = -1;
}

//Destructor for web server
WebServer::~WebServer()
{
    if (server_fd_ != -1)
    {
        close(server_fd_);
    }
    std::cout << "[INFO] WebServer destroyed.\n";
}


//Creates a socket,binds it to given port and starts listening.
void WebServer::initializeSocket()
{
    struct addrinfo *res = resolveAddress(port_);

    server_fd_ = createSocket(
        res->ai_family,
        res->ai_socktype,
        res->ai_protocol);

    bindSocket(server_fd_, res);
    listenOnSocket(server_fd_, 10); // backlog size = 10

    freeaddrinfo(res); // Clean up memory returned by getaddrinfo
}

//Accepts client side connections and sends a response accordinly.
void WebServer::acceptAndRespond()
{
    std::cout << "[INFO] Waiting for clients on port " << port_ << "...\n";
    while (true) {     //temporary fix to avoid closing after one conection
        int client_fd = acceptClient();
        if (client_fd == -1)
            continue; // Try next client

        sendResponse(client_fd);
        closeConnection(client_fd);
    }
}

int WebServer::acceptClient()
{
    struct sockaddr_storage client_addr;
    socklen_t addr_size = sizeof(client_addr);

    int client_fd = accept(server_fd_, (struct sockaddr *)&client_addr, &addr_size);
    if (client_fd == -1)
    {
        std::cerr << "[ERROR] Failed to accept client: " << strerror(errno) << "\n";
    }
    else
    {
        std::cout << "[INFO] Client connected.\n";
    }

    return client_fd;
}

void WebServer::sendResponse(int client_fd) {
    char buffer[2048];
    // receiving request from client and storing in buffer
    int bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (bytes_received <= 0) {
        std::cerr << "[ERROR] Failed to read from client.\n";
        return;
    }

    buffer[bytes_received] = '\0';
    std::string request = buffer;

    // Extract array elements from body
    std::vector<int> nums = parseJsonArray(request);


    std::sort(nums.begin(), nums.end());


    std::string response_body = buildJsonResponse(nums);

    sendHttpResponse(client_fd, response_body);

    std::cout << "[INFO] Responded with sorted array.\n";
}


void WebServer::closeConnection(int client_fd)
{
    close(client_fd);
    std::cout << "[INFO] Closed client connection.\n";
}
