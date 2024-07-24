#include "XaddCommand.hpp"
#include <iostream>
#include <sstream>
#include "../Store/KeyValueStore.hpp"

XaddCommand::XaddCommand() {}

std::vector<std::string> XaddCommand::execute(const std::vector<std::string>& args) {
    std::cout << "XaddCommand was it here?:\n-----------" << std::endl;
    std::cout << "size: " <<args.size() << std::endl;
    if (args.size() == 4) {
        std::string streamKey = args[1];
        std::string id = args[2];

        std::istringstream iss(args[3]);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        std::unordered_map<std::string, std::string> fieldValues;
        for (size_t i = 0; i < tokens.size(); i += 2) {
            fieldValues[tokens[i]] = tokens[i + 1];
        }
        for(const auto& tokenPair: fieldValues) {
            std::cout << tokenPair.first << " " << tokenPair.second << std::endl;
        }
        std::cout << "XaddCommand was it here?:\n++++++" << std::endl;
        return {KeyValueStore::getInstance().xadd(streamKey, id, fieldValues)};
        
    }
    return {"-ERR wrong number of arguments"};
}
