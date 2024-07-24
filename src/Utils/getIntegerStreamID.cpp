

#include "utils.hpp"
#include <string>
#include <sstream>
#include <chrono>
#include <iostream>

namespace utils {
     long long getStreamIDStringMillisecondsTime(const std::string& input) {
        size_t dashPos = input.find('-');
        if (dashPos == std::string::npos) {
            return -1LL;
        }

        std::string strMST = input.substr(0, dashPos);

        long long inputMST;

        try {
            inputMST = std::stoll(strMST);
            return inputMST;
        } catch (const std::invalid_argument& e) {
            return -1LL;
        } catch (const std::out_of_range& e) {
            return -1LL;
        }

    }

    int getStreamIDStringSequenceNumber(const std::string& input) {
        size_t dashPos = input.find('-');
        if (dashPos == std::string::npos) {
            return -1;
        }

        std::string strSN = input.substr(dashPos + 1);

        int inputSN;

        try {
            inputSN = std::stoi(strSN);
            return inputSN;
        } catch (const std::invalid_argument& e) {
            return -1;
        } catch (const std::out_of_range& e) {
            return -1;
        }

    }

    void setStreamIDNumbers(const std::string& input, long long& millisecondsTime, int& sequenceNumber) {
      size_t dashPos = input.find('-');
      size_t asteriskPos = input.find('*');

      if (input == "*") {
        // Auto-generate using current Unix time in milliseconds
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epoch = now_ms.time_since_epoch();
        long long newMillisecondsTime = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();

        if (newMillisecondsTime == millisecondsTime) {
          sequenceNumber++;
        } else {
          millisecondsTime = newMillisecondsTime;
          sequenceNumber = 0;
        }
        return;
      }

      if (dashPos != std::string::npos && asteriskPos == std::string::npos) {
        // Normal ID processing when input is like "1234567890-1"
        millisecondsTime = utils::getStreamIDStringMillisecondsTime(input);
        sequenceNumber = utils::getStreamIDStringSequenceNumber(input);
        return;
      }

      if (asteriskPos != std::string::npos && input.back() == '*') {
        // Handle the case where time is specified but sequence number is auto-incremented
        std::cout << "Handle the case where time is specified but sequence number is auto-incremented" << std::endl;
        std::string timePart = input.substr(0, asteriskPos);
        long long streamIDsMilliSeconds = utils::getStreamIDStringMillisecondsTime(timePart);

        if (streamIDsMilliSeconds == millisecondsTime) {
          sequenceNumber++;
        } else {
          millisecondsTime = streamIDsMilliSeconds;
          sequenceNumber = 0;
        }
      }
    }
}
