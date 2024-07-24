#include "XreadCommand.hpp"
#include <iostream>
#include <sstream>
#include "../Store/KeyValueStore.hpp"

XreadCommand::XreadCommand() {}

std::vector<std::string> XreadCommand::execute(const std::vector<std::string>& args) {
    std::cout << "XrangeCommand was it here?:\n-----------" << std::endl;
    if (args.size() >= 4 && args.size()%2==0 ) {
      std::vector<std::string> streamKeys = {};
      std::vector<std::string> ids = {};
      int lenOfStreamIDs = args.size()-2;
      for(int i = 0; i < lenOfStreamIDs;i++){
        if(i<(lenOfStreamIDs/2)){
          streamKeys.push_back(args[2+i]);
        }else{
          ids.push_back(args[2+i]);
        }
      }
      std::vector<std::pair<Stream, std::string>> streams = {};
      for(int i=0; i<streamKeys.size();i++){
        std::string streamKey = streamKeys[i];
        std::string id = ids[i];
        std::cout << "Stream is " << streamKey << std::endl;
        std::cout << "id is " << id << std::endl;
        Stream stream = KeyValueStore::getInstance().xread(streamKey, id);
        streams.push_back({stream, streamKey});
      }
      return formatForRESP(streams);
      
    }
    return {"-ERR wrong number of arguments"};
}

std::vector<std::string> XreadCommand::formatForRESP(const std::vector<std::pair<Stream, std::string>>& streams) {
    std::vector<std::string> formattedEntries;
    formattedEntries.push_back("*" + std::to_string(streams.size()));
    for(const auto& streamPair : streams){
      Stream stream = streamPair.first;
      std::string streamKey = streamPair.second;
      
      formattedEntries.push_back("*" + std::to_string(2));
      formattedEntries.push_back("$" + streamKey);
      formattedEntries.push_back("*" + std::to_string(stream.size())); // Size of the array
      for (const auto& entry : stream) {
          formattedEntries.push_back("*2"); // Each entry has 2 elements (ID and array of fields)
          formattedEntries.push_back("$" + entry.id); // Stream entry ID
          formattedEntries.push_back("*" + std::to_string(entry.fields.size() * 2)); // Number of fields * 2 (field name and value)
          for (const auto& field : entry.fields) {
              formattedEntries.push_back("$" + field.first); // Field name
              formattedEntries.push_back("$" + field.second); // Field value
          }
      }
    }
    
    return formattedEntries;
}
