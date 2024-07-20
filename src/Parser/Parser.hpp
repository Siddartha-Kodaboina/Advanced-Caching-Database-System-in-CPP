#pragma once
#include <string>
#include <vector>

class Parser {
public:
  std::vector<std::string> decode(const std::string& input);
  std::string encode(const std::vector<std::string>& response);
};
