#include "utils.hpp"

namespace utils {
  std::string getRawString(const std::string& input) {
    std::ostringstream oss;
    for (char ch : input) {
      switch (ch) {
        case '\r':
          oss << "\\r";
          break;
        case '\n':
          oss << "\\n";
          break;
        default:
          oss << ch;
      }
    }
    return oss.str();
  }
}
