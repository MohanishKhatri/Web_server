// WebServer.hpp

#pragma once
#include <string>
#include "SocketUtils.hpp"

class WebServer {
public:
    WebServer(const std::string& port);
    ~WebServer();
    void initializeSocket();
    void acceptAndRespond();

private:
    std::string port_;
    int server_fd_;   

    int acceptClient();
    void sendResponse(int client_fd, const std::string& message);
    void closeConnection(int client_fd);
};
