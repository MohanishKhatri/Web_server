# Simple C++ Web Server

This project is a minimal web server written in modern C++ for learning socket programming. It demonstrates how to create, bind, listen, and accept TCP connections using C++ and POSIX sockets.

## Features

- Uses modern C++ style (no C-style `memset`)
- Supports both IPv4 and IPv6
- Handles one client connection at a time
- Sends a simple greeting message to the client

## Files

- `main.cpp` — Entry point, starts the server
- `WebServer.hpp` / `WebServer.cpp` — WebServer class: manages socket setup, accepting clients, and sending responses
- `SocketUtils.hpp` / `SocketUtils.cpp` — Utility functions for socket operations
- `README.md` — This file

## How to Build

Make sure you have `g++` installed.

```bash
g++ -o webserver main.cpp WebServer.cpp SocketUtils.cpp
```

## How to Run

Start the server:

```bash
./webserver
```

In another terminal, connect as a client (using `telnet` or `nc`):

```bash
telnet 127.0.0.1 8080
# or
nc 127.0.0.1 8080
```

You should see the message:

```
Hello from server
```
