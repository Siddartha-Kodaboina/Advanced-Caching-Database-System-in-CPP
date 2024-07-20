#include "utils.hpp"
#include <algorithm> 
#include <cctype>  

namespace utils {
  std::string toLowerCase(const std::string& input) {
      std::string lowerCaseStr = input;
    std::transform(lowerCaseStr.begin(), lowerCaseStr.end(), lowerCaseStr.begin(),
                  [](unsigned char c) { return std::tolower(c); });
    return lowerCaseStr;
  }
}
