

#include "utils.hpp"
#include <string>
#include <sstream>

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
}
