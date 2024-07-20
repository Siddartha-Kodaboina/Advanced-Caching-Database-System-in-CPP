#pragma once
#include "ICommand.hpp"
#include "../Store/KeyValueStore.hpp"

class SetCommand : public ICommand {
private:
    KeyValueStore& store;
public:
    SetCommand(KeyValueStore& kvStore);
    std::vector<std::string> execute(const std::vector<std::string>& args) override;
};
