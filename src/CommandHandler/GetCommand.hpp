#pragma once
#include "ICommand.hpp"
#include "../Store/KeyValueStore.hpp"
#include "../Utils/utils.hpp"

class GetCommand : public ICommand {
private:
    KeyValueStore& store;
public:
    GetCommand(KeyValueStore& kvStore);
    std::vector<std::string> execute(const std::vector<std::string>& args) override;
};
