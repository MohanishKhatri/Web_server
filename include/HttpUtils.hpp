#pragma once
#include <string>
#include <vector>

std::vector<int> parseJsonArray(const std::string& client_request);

void sendHttpResponse(int client_fd, const std::string& response_body);

std::string buildJsonResponse(const std::vector<int>& nums);
