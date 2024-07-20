#pragma once
#include "ICommand.hpp"
#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>
#include "PingCommand.hpp"
#include "EchoCommand.hpp"
#include "SetCommand.hpp"
#include "GetCommand.hpp"

class CommandFactory {
private:
  std::unordered_map<std::string, std::unique_ptr<ICommand>> commandMap;
  KeyValueStore& store;
public:
  CommandFactory(KeyValueStore& kvStore);
  ICommand* getCommand(const std::string& commandName);
  static std::string toLower(const std::string& str);
};
