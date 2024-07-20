#pragma once
#include<iostream>
#include "ICommand.hpp"

class PingCommand : public ICommand {
public:
  std::vector<std::string> execute(const std::vector<std::string>& args) override;
};
