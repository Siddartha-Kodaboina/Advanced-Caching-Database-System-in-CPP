#pragma once
#include "ICommand.hpp"
#include "../Store/KeyValueStore.hpp"

class XrangeCommand : public ICommand {

public:
    XrangeCommand();
    std::vector<std::string> execute(const std::vector<std::string>& args) override;
    std::vector<std::string> formatForRESP(const Stream& entries);
};
