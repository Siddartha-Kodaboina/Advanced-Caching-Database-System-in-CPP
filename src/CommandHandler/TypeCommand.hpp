#pragma once
#include "ICommand.hpp"


class TypeCommand : public ICommand {

public:
    TypeCommand();
    std::vector<std::string> execute(const std::vector<std::string>& args) override;
};
