#include "PingCommand.hpp"


std::vector<std::string> PingCommand::execute(const std::vector<std::string>& args) {
  std::cout << "Ping Command" << std::endl;
  return {"+PONG"};
}
