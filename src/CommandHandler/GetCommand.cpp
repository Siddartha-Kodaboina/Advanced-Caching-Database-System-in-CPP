#include "GetCommand.hpp"
#include<iostream>

GetCommand::GetCommand(KeyValueStore& kvStore) : store(kvStore) {}

std::vector<std::string> GetCommand::execute(const std::vector<std::string>& args) {
    if (args.size() == 2) {
        std::cout << "here in get inside if " << utils::getRawString(args[1]) << std::endl;
        std::string returned_value = store.get(args[1]);
        return {'+'+returned_value};
    }
    std::cout << "here in get after if " << std::endl;
    std::string errorCode = "-1"; 
    return {"+" + errorCode};
}
