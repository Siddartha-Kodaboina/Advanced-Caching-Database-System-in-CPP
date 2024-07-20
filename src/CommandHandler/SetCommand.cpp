#include "SetCommand.hpp"
#include<iostream>
#include "../Store/KeyValueStore.hpp"

SetCommand::SetCommand() {}

std::vector<std::string> SetCommand::execute(const std::vector<std::string>& args) {
    if (args.size() == 5) {
        int ttl = std::stoi(args[4]);
        std::cout << "time to live in seconds: " << ttl << std::endl;
        std::cout << args[1] << " " << args[2]<< " " <<  ttl << std::endl;
        KeyValueStore::getInstance().set(args[1], args[2], args[3], ttl);
        return {"+OK"};
    }
    else if (args.size() == 3){
        KeyValueStore::getInstance().set(args[1], args[2]);
        return {"+OK"};
    }
    return {"-ERR wrong number of arguments"};
}
