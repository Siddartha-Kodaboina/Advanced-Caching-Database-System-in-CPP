#include "EchoCommand.hpp"


std::vector<std::string> EchoCommand::execute(const std::vector<std::string>& args) {
  if(args.size()<5){
    return {"+EchoCommand"};
  }
  return {args[4]};
}
