#include "SetCommand.hpp"
#include<iostream>

SetCommand::SetCommand(KeyValueStore& kvStore) : store(kvStore) {}

std::vector<std::string> SetCommand::execute(const std::vector<std::string>& args) {
    if (args.size() == 4) {
        int ttl = std::stoi(args[3]);
        std::cout << "time to live in seconds: " << ttl << std::endl;
        std::cout << args[1] << " " << args[2]<< " " <<  ttl << std::endl;
        store.set(args[1], args[2], ttl);
        return {"+OK"};
    }
    return {"-ERR wrong number of arguments"};
}
