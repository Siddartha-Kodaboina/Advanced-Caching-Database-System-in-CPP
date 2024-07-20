#pragma once
#include <vector>
#include <string>

class ICommand {
public:
  virtual ~ICommand() = default;
  virtual std::vector<std::string> execute(const std::vector<std::string>& args) = 0;
};
