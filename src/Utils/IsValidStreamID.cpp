#include "utils.hpp"
#include <string>
#include <iostream>
#include <sstream>

namespace utils {
    int IsValidStreamID(const std::string& input,const long long& millisecondsTime,const int& sequenceNumber) {
        std::cout << "IsValidStreamID " << input << std::endl;
        if(input=="*"){
            return 0;
        }
        size_t dashPos = input.find('-');
        if (dashPos == std::string::npos) {
            return -1;
        }

        std::string strMST = input.substr(0, dashPos);
        std::string strSN = input.substr(dashPos + 1);

        long long inputMST;
        int inputSN;

        try {
            inputMST = std::stoll(strMST);
            if(strSN=="*"){
                std::cout << "Star match " << strSN << std::endl;
                if(inputMST>=millisecondsTime){
                    return 0;
                }else{
                    return 2;
                }
            }
            inputSN = std::stoi(strSN);
        } catch (const std::invalid_argument& e) {
            return -1;
        } catch (const std::out_of_range& e) {
            return -1;
        }

        if (inputMST == 0 && inputSN == 0) {
            return 1;
        } else if (inputMST < millisecondsTime) {
            return 2;
        } else if (inputMST == millisecondsTime && inputSN <= sequenceNumber) {
            return 2;
        } else {
            return 0;
        }
    }
}
