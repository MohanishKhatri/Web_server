# Simple C++ Web Server

This project is a minimal web server written in modern C++ for learning socket programming and basic HTTP handling. It demonstrates how to create, bind, listen, and accept TCP connections, parse a JSON array from HTTP requests, sort it, and respond with the sorted array.

## Features

- Supports both IPv4 and IPv6
- Handles multiple client connections (one at a time, in a loop, or with epoll)
- Parses a JSON array from HTTP POST requests, sorts it, and returns the sorted array as JSON
- Simple, modular codebase for learning and extension

## Project Structure

```
Web_server/
├── include/
│   ├── WebServer.hpp
│   ├── SocketUtils.hpp
│   └── HttpUtils.hpp
├── src/
│   ├── main.cpp
│   ├── WebServer.cpp
│   ├── SocketUtils.cpp
│   └── HttpUtils.cpp
├── Makefile
├── README.md
├── BenchmarkResults.md
```

## How to Build

From the project root, simply run:

```bash
make build
```

## How to Run

Start the server with:

```bash
make run
```

To clean up the build output:

```bash
make clean
```

## How to Test

You can use `curl`, `nc`, or any HTTP client. For example, with `curl`:

```bash
curl -X POST -H "Content-Type: application/json" -d '[3,1,2,-5]' http://127.0.0.1:8080/
```

Or with `nc`:

```bash
echo -e "POST / HTTP/1.1\r\nHost: localhost\r\nContent-Type: application/json\r\nContent-Length: 13\r\n\r\n[3,1,2,-5]" | nc 127.0.0.1 8080
```

Expected response:

```
HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 21

{"result": [-5, 1, 2, 3]}
```

## Benchmarking

We benchmarked the server using ApacheBench (`ab`) to evaluate its performance under concurrent load.

**See [BenchmarkResults.md](BenchmarkResults.md) for detailed results comparing blocking and epoll modes.**

## References & Resources

- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/) — Excellent introduction to socket programming in C/C++.
- [man 2 socket](https://man7.org/linux/man-pages/man2/socket.2.html) — Linux manual page for the `socket` system call.
- [man 7 epoll](https://man7.org/linux/man-pages/man7/epoll.7.html) — Linux manual page for the `epoll` API.
- [cppreference.com](https://en.cppreference.com/w/) — C++ standard library reference.

---

Feel free to extend this project or use it as a base for more advanced networking and HTTP experiments!
