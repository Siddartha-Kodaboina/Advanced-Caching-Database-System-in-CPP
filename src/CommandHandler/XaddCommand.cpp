#include "XaddCommand.hpp"
#include <iostream>
#include "../Store/KeyValueStore.hpp"

XaddCommand::XaddCommand() {}

std::vector<std::string> XaddCommand::execute(const std::vector<std::string>& args) {
    if (args.size() >= 5 && (args.size() % 2) == 1) {
        std::string streamKey = args[1];
        std::string id = args[2];

        std::unordered_map<std::string, std::string> fieldValues;
        for (size_t i = 3; i < args.size(); i += 2) {
            fieldValues[args[i]] = args[i + 1];
        }

        return {KeyValueStore::getInstance().xadd(streamKey, id, fieldValues)};
        
    }
    return {"-ERR wrong number of arguments"};
}
