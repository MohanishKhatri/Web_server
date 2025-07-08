# Simple C++ Web Server

This project is a minimal web server written in modern C++ for learning socket programming and basic HTTP handling. It demonstrates how to create, bind, listen, and accept TCP connections, parse a JSON array from HTTP requests, sort it, and respond with the sorted array.

## Features

- Supports both IPv4 and IPv6
- Handles multiple client connections (one at a time, in a loop)
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
├── README.md
```

## How to Build

From the project root, run:

```bash
g++ -Iinclude -o webserver src/main.cpp src/WebServer.cpp src/SocketUtils.cpp src/HttpUtils.cpp
```

## How to Run

Start the server:

```bash
./webserver
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

For example, with the following command:

```bash
echo '[3,1,2,-5]' > data.json
ab -n 100 -c 10 -p data.json -T application/json http://127.0.0.1:8080/
```

### Benchmark Results

```
Concurrency Level:      10
Time taken for tests:   0.008 seconds
Complete requests:      100
Failed requests:        0
Requests per second:    12128.56 [#/sec] (mean)
Time per request:       0.825 [ms] (mean)
Transfer rate:          1137.05 [Kbytes/sec] received
```

**Conclusions:**
- The server is capable of handling over 12,000 requests per second with 10 concurrent clients on a typical local machine.
- All requests completed successfully with no failures.
- The average response time per request was less than 1 millisecond.
- This demonstrates that even a simple, single-threaded C++ server can achieve high throughput for lightweight tasks.

---

Feel free to extend this project or use it as a base for more advanced
