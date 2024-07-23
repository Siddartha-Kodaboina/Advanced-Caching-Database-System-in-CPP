#include "GetCommand.hpp"
#include <iostream>
#include <variant>
#include "../Store/KeyValueStore.hpp"
#include "../Utils/utils.hpp"

GetCommand::GetCommand() {}

std::vector<std::string> GetCommand::execute(const std::vector<std::string>& args) {
    if (args.size() == 2) {
        std::cout << "here in get inside if " << utils::getRawString(args[1]) << std::endl;
        Value returned_value = KeyValueStore::getInstance().get(args[1]);

        // Use std::visit to handle the different types within Value
        std::string result = std::visit([](auto&& arg) -> std::string {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::string>) {
                return '$' + arg;  // Directly return the string with a prefix
            } else if constexpr (std::is_same_v<T, std::shared_ptr<KeyValue>>) {
                // If it is a nested KeyValue, you might want to perform some specific action
                return "Nested KeyValue type";  // Placeholder for actual handling
            } else {
                return "Unsupported type in KeyValueStore";
            }
        }, returned_value);

        return {result};
    }
    std::cout << "here in get after if " << std::endl;
    std::string errorCode = "-1";
    return {"+" + errorCode};
}
