#include "Parser.hpp"
#include <sstream>
#include <iostream>

std::vector<std::string> Parser::decode(const std::string& input) {
  std::vector<std::string> commands;
  std::istringstream iss(input);
  std::string segment;
  while (std::getline(iss, segment, '\r')) {
    auto pos = segment.find('\n');
    if (pos != std::string::npos) segment.erase(pos, 1);
    if (segment[0]=='*' || segment[0]=='$') continue;
    if (!segment.empty()) commands.push_back(segment);
  }

  return commands;
}

std::string Parser::encode(const std::vector<std::string>& response) {
  std::ostringstream oss;
  for (auto& part : response) {
    if (part.empty()) continue;
    std::string mutable_part = part; 
    char firstChar = mutable_part[0];
    mutable_part.erase(0, 1);
    if (firstChar=='+'){
      oss << "+" << mutable_part << "\r\n";
    }
    else{
      oss << "$" << mutable_part.size() << "\r\n" << mutable_part << "\r\n";
    }
    
  }
  return oss.str();
}
