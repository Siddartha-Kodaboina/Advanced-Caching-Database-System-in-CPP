#pragma once
#include<iostream>
#include "ICommand.hpp"

class EchoCommand : public ICommand {
public:
  std::vector<std::string> execute(const std::vector<std::string>& args) override;
};
