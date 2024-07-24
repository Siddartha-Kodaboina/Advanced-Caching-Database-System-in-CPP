#pragma once
#include "ICommand.hpp"
#include "../Store/KeyValueStore.hpp"

class XreadCommand : public ICommand {

public:
    XreadCommand();
    std::vector<std::string> execute(const std::vector<std::string>& args) override;
    std::vector<std::string> formatForRESP(const std::vector<std::pair<Stream, std::string>>& entries);
};
