# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Source and target
SRC = src/main.cpp src/WebServer.cpp src/SocketUtils.cpp src/HttpUtils.cpp
TARGET = webserver

# Default build
all: build

# Build rule
build:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	@echo "[✔] Build complete."

# Run server
run: build
	./$(TARGET)


# Clean build
clean:
	rm -f $(TARGET)
	@echo "[✘] Cleaned build artifacts."
