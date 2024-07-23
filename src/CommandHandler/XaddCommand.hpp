#pragma once
#include "ICommand.hpp"
#include "../Store/KeyValueStore.hpp"

class XaddCommand : public ICommand {

public:
    XaddCommand();
    std::vector<std::string> execute(const std::vector<std::string>& args) override;
};
