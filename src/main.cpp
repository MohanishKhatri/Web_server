#include "WebServer.hpp"

int main() {
    WebServer server("8080");      // Giving port to be used by server
    server.initializeSocket();     //Creates  socket and binds it to above given port and starts listening.
    // server.acceptAndRespond();      //Accepts and handles one client at a time
    server.runWithEpoll();         // Accepts and handles multiple clients using epoll
}

