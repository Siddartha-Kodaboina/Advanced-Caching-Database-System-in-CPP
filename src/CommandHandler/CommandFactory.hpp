#pragma once
#include "ICommand.hpp"
#include <unordered_map>
#include <memory>
#include <string>
#include<iostream>

class CommandFactory {
private:
  std::unordered_map<std::string, std::unique_ptr<ICommand>> commandMap;
public:
  CommandFactory();
  ICommand* getCommand(const std::string& commandName);
  static std::string toLower(const std::string& str);
};