#include "XrangeCommand.hpp"
#include <iostream>
#include "../Store/KeyValueStore.hpp"

XrangeCommand::XrangeCommand() {}

std::vector<std::string> XrangeCommand::execute(const std::vector<std::string>& args) {
    std::cout << "XrangeCommand was it here?:\n-----------" << std::endl;
    if (args.size() >= 4 ) {
        std::string streamKey = args[1];
        std::string start = args[2];
        std::string end = args[3];
        std::cout << "XaddCommand was it here?:\n++++++" << std::endl;
        auto entries = KeyValueStore::getInstance().xrange(streamKey, start, end);
        return formatForRESP(entries);
        
    }
    return {"-ERR wrong number of arguments"};
}

std::vector<std::string> XrangeCommand::formatForRESP(const Stream& entries) {
    std::vector<std::string> formattedEntries;
    formattedEntries.push_back("*" + std::to_string(entries.size())); // Size of the array
    for (const auto& entry : entries) {
        formattedEntries.push_back("*2"); // Each entry has 2 elements (ID and array of fields)
        formattedEntries.push_back("+" + entry.id); // Stream entry ID
        formattedEntries.push_back("*" + std::to_string(entry.fields.size() * 2)); // Number of fields * 2 (field name and value)
        for (const auto& field : entry.fields) {
            formattedEntries.push_back("+" + field.first); // Field name
            formattedEntries.push_back("+" + field.second); // Field value
        }
    }
    return formattedEntries;
}
