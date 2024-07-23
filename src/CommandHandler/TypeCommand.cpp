#include "GetCommand.hpp"
#include "TypeCommand.hpp"
#include<iostream>

TypeCommand::TypeCommand() {}

std::vector<std::string> TypeCommand::execute(const std::vector<std::string>& args) {
  std::cout << "Executing in TypeComnad.cpp" << std::endl;
  GetCommand getCmd;
  auto value = getCmd.execute(args);
  std::cout << value[0][0] << std::endl;
  std::string type = "none";
  if (!value.empty() && value[0][0] == '$' && value[0].size()!=1) {
      type = "string";
      return {'+'+type};
  }
  return {'+'+type};
}
