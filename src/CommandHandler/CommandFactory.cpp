#include "CommandFactory.hpp"
#include "PingCommand.hpp"
#include "EchoCommand.hpp"
#include "SetCommand.hpp"
#include "GetCommand.hpp"
#include "TypeCommand.hpp"
#include <algorithm> 
#include <cctype>  

CommandFactory::CommandFactory() {
  commandMap["ping"] = std::make_unique<PingCommand>();
  commandMap["echo"] = std::make_unique<EchoCommand>();
  commandMap["set"] = std::make_unique<SetCommand>();
  commandMap["get"] = std::make_unique<GetCommand>();
  commandMap["type"] = std::make_unique<TypeCommand>();
}

ICommand* CommandFactory::getCommand(const std::string& commandName) {
  std::string lowerCaseCommand = toLower(commandName);
  std::cout << "In command factory: " << lowerCaseCommand << std::endl;
  auto it = commandMap.find(lowerCaseCommand);
  if (it != commandMap.end()) {
    return it->second.get();
  }
  return nullptr;
}

std::string CommandFactory::toLower(const std::string& str) {
  std::string lowerCaseStr = str;
  std::transform(lowerCaseStr.begin(), lowerCaseStr.end(), lowerCaseStr.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return lowerCaseStr;
}
