#include "HttpUtils.hpp"
#include <cctype>
#include <string>
#include <sys/socket.h>

// Extracts integer values from JSON string
std::vector<int> parseJsonArray(const std::string& client_request) {
    std::vector<int> result;
    bool inside_array = false;
    std::string num;

    for (char i : client_request) {
        if (i == '[') {
            inside_array = true;
        } else if (i  == ']') {
            if (!num.empty()) {
                result.push_back(std::stoi(num));
                num.clear();
            }
            break;
        } else if (inside_array) {
            if (isdigit(i) || i == '-') {
                num += i;
            } else if (i == ',' && !num.empty()) {
                result.push_back(std::stoi(num)); //string to int(stoi)
                num.clear();
            } else if (isspace(i)) {
                continue;   //ignores space
            }
        }
    }

    return result;
}

// converts sorted vector of int to JSON again
std::string buildJsonResponse(const std::vector<int>& nums) {
    std::string result = "{\"result\": [";

    for (size_t i = 0; i < nums.size(); ++i) {
        result += std::to_string(nums[i]);
        if (i != nums.size() - 1) {
            result += ", ";
        }
    }

    result += "]}";
    return result;
}

//Sends sorted array as JSON back to client
void sendHttpResponse(int client_fd, const std::string& response_body) {
    std::string response;

    response += "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: application/json\r\n";  //application/json tells client what format response is in
    response += "Content-Length: " + std::to_string(response_body.length()) + "\r\n";
    response += "\r\n";
    response += response_body;

    send(client_fd, response.c_str(), response.size(), 0);
}

