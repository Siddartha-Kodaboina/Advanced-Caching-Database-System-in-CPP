#pragma once
#include <string>
#include <sstream>

namespace utils {
  std::string getRawString(const std::string& input);
  std::string toLowerCase(const std::string& input);
  int IsValidStreamID(const std::string& input, const long long& millisecondsTime, const int& sequenceNumber);
  long long getStreamIDStringMillisecondsTime(const std::string& input);
  int getStreamIDStringSequenceNumber(const std::string& input);
}
