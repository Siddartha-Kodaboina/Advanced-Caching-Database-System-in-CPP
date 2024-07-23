#include "Parser.hpp"
#include <sstream>
#include <iostream>

std::vector<std::string> Parser::decode(const std::string& input) {
  std::vector<std::string> commands;
  std::istringstream iss(input);
  std::string segment;
  int ind=0;
  while (std::getline(iss, segment, '\r')) {
    auto pos = segment.find('\n');
    if (pos != std::string::npos) segment.erase(pos, 1);
    if (ind==0 && segment[0]=='*') {
      ind += 1;
      continue;
    }
    if(segment[0]=='$') continue;
    if (!segment.empty()) commands.push_back(segment);
  }

  return commands;
}

// std::string Parser::encode(const std::vector<std::string>& response) {
//   std::ostringstream oss;
//   for (auto& part : response) {
//     if (part.empty()) continue;
//     std::string mutable_part = part; 
//     char firstChar = mutable_part[0];
//     mutable_part.erase(0, 1);

//     if (firstChar=='+'){
//       oss << "+" << mutable_part << "\r\n";
//     }
//     else if (firstChar=='-'){
//       oss << "-" << mutable_part << "\r\n";
//     }
//     else{
//       if (mutable_part.size()){
//         oss << "$" << mutable_part.size() << "\r\n" << mutable_part << "\r\n";
//       }else{
//         oss << "$" <<  "-1" << "\r\n";
//       }
      
//     }
    
//   }
//   return oss.str();
// }

std::string Parser::encode(const std::vector<std::string>& response) {
  std::ostringstream oss;
  for (const auto& part : response) {
      if (part.empty()) continue;
      char type = part[0];
      std::string content = part.substr(1);

      switch (type) {
          case '+': // Simple strings
              oss << "+" << content << "\r\n";
              break;
          case '-': // Errors
              oss << "-" << content << "\r\n";
              break;
          case ':': // Integers
              oss << ":" << content << "\r\n";
              break;
          case '$': // Bulk strings
              if (content == "-1" || content=="") {
                  oss << "$-1\r\n";
              } else {
                  oss << "$" << content.size() << "\r\n" << content << "\r\n";
              }
              break;
          case '*': // Arrays
              oss << "*" << content << "\r\n";
              break;
          default:
              // Handle unexpected cases or log errors
              break;
      }
  }
  return oss.str();
}

