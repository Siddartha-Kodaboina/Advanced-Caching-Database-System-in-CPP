#pragma once
#include "ICommand.hpp"
#include "../Store/KeyValueStore.hpp"

class SetCommand : public ICommand {

public:
    SetCommand();
    std::vector<std::string> execute(const std::vector<std::string>& args) override;
};
