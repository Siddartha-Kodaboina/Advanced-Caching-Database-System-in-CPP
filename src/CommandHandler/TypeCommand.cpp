#include "TypeCommand.hpp"
#include "../Store/KeyValueStore.hpp"
#include<iostream>

TypeCommand::TypeCommand() {}

std::vector<std::string> TypeCommand::execute(const std::vector<std::string>& args) {
  std::cout << "Executing in TypeComnad.cpp" << std::endl;
  if (args.size()>1){
    return {'+'+KeyValueStore::getInstance().type(args[1])};
  }
  std::string type = "none";
  return {'+'+type};
}
