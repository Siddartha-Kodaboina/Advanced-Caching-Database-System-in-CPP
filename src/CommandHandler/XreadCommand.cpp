#include "XreadCommand.hpp"
#include <iostream>
#include <sstream>
#include "../Store/KeyValueStore.hpp"

XreadCommand::XreadCommand() {}

std::vector<std::string> XreadCommand::execute(const std::vector<std::string>& args) {
    std::cout << "XrangeCommand was it here?:\n-----------" << std::endl;
    if (args.size() == 4 ) {
        std::string streamKey = args[2];
        std::string id = args[3];
        std::cout << "XaddCommand was it here?:\n++++++" << std::endl;
        auto entries = KeyValueStore::getInstance().xread(streamKey, id);
        return formatForRESP(entries, streamKey);
        
    }
    return {"-ERR wrong number of arguments"};
}

std::vector<std::string> XreadCommand::formatForRESP(const Stream& entries, std::string streamKey) {
    std::vector<std::string> formattedEntries;
    formattedEntries.push_back("*" + std::to_string(1));
    formattedEntries.push_back("*" + std::to_string(2));
    formattedEntries.push_back("$" + streamKey);
    formattedEntries.push_back("*" + std::to_string(entries.size())); // Size of the array
    for (const auto& entry : entries) {
        formattedEntries.push_back("*2"); // Each entry has 2 elements (ID and array of fields)
        formattedEntries.push_back("$" + entry.id); // Stream entry ID
        formattedEntries.push_back("*" + std::to_string(entry.fields.size() * 2)); // Number of fields * 2 (field name and value)
        for (const auto& field : entry.fields) {
            formattedEntries.push_back("$" + field.first); // Field name
            formattedEntries.push_back("$" + field.second); // Field value
        }
    }
    return formattedEntries;
}
