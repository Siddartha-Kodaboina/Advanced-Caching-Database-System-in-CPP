#include "EchoCommand.hpp"


std::vector<std::string> EchoCommand::execute(const std::vector<std::string>& args) {
  if(args.size()<5){
    return {"(nil)"};
  }
  return {args[4]};
}
