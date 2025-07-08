# Benchmark Results - Async C++ Web Server (Blocking vs Epoll)

These benchmarks compare the performance of the server in blocking mode and epoll mode using ApacheBench (`ab`).

---

## TEST 1: Light Load - 100 requests, 10 concurrent clients

**Command:**
```bash
ab -n 100 -c 10 -p data.json -T application/json http://127.0.0.1:8080/
```

| Version   | Requests/sec | Avg Time/Request | Max Time | Failed Requests |
|-----------|--------------|------------------|----------|----------------|
| Blocking  | 12,128.56    | 0.825 ms         | 1 ms     | 0              |
| Epoll     | 16,889.04    | 0.592 ms         | 1 ms     | 0              |

_Epoll handled ~39% more requests/sec with lower latency._

---

## TEST 2: Stress Test - 1000 requests, 50 concurrent clients

**Command:**
```bash
ab -n 1000 -c 50 -p data.json -T application/json http://127.0.0.1:8080/
```

| Version   | Requests/sec | Avg Time/Request | Max Time | Failed Requests |
|-----------|--------------|------------------|----------|----------------|
| Blocking  | 6,501.78     | 7.69 ms          | 5 ms     | 0              |
| Epoll     | 7,040.07     | 7.10 ms          | 4 ms     | 0              |

_Epoll version showed better scalability and slightly improved latency under load._

---

## Summary

- Epoll outperformed blocking in both light and high concurrency scenarios.
- No failed requests in any test.
- Server maintained sub-millisecond latency for typical workloads.

---

For a quick summary, see the main [README.md](README.md).