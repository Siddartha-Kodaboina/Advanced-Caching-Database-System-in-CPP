#include "Parser.hpp"
#include <sstream>

std::vector<std::string> Parser::decode(const std::string& input) {
  std::vector<std::string> commands;
  std::istringstream iss(input);
  std::string segment;

  while (std::getline(iss, segment, '\r')) {
    auto pos = segment.find('\n');
    if (pos != std::string::npos) segment.erase(pos, 1);
    if (!segment.empty()) commands.push_back(segment);
  }

  return commands;
}

std::string Parser::encode(const std::vector<std::string>& response) {
  std::ostringstream oss;
  for (const auto& part : response) {
    oss << "$" << part.size() << "\r\n" << part << "\r\n";
  }
  return oss.str();
}
