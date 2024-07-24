#include "KeyValueStore.hpp"
#include "../Utils/utils.hpp"
#include <iostream>
#include <limits>

KeyValue& KeyValueStore::getInstance() {
    static KeyValue instance;
    return instance;
}

void KeyValue::set(const std::string& key, const Value& value) {
    std::lock_guard<std::mutex> lock(storeMutex);
    store[key] = {value, std::nullopt};
}

void KeyValue::set(const std::string& key, const Value& value, const std::string& timeType, int ttl) {
    std::lock_guard<std::mutex> lock(storeMutex);
    auto expiry = std::chrono::steady_clock::now() + (timeType == "EX" ? std::chrono::seconds(ttl) : std::chrono::milliseconds(ttl));
    store[key] = {value, expiry};
}

Value KeyValue::get(const std::string& key) {
    std::lock_guard<std::mutex> lock(storeMutex);
    auto it = store.find(key);
    if (it != store.end() && (!it->second.expiration || std::chrono::steady_clock::now() < it->second.expiration.value())) {
        return it->second.value;
    }
    return "";
}

bool KeyValue::del(const std::string& key) {
    std::lock_guard<std::mutex> lock(storeMutex);
    return store.erase(key) > 0;
}

std::string KeyValue::xadd(const std::string& streamKey, const std::string& id, const std::unordered_map<std::string, std::string>& fieldValues) {
    std::lock_guard<std::mutex> lock(storeMutex);
    int returnCode = utils::IsValidStreamID(id, millisecondsTime, sequenceNumber);
    if(returnCode==0){
      utils::setStreamIDNumbers(id, millisecondsTime, sequenceNumber);
      if (!store.count(streamKey) || !std::holds_alternative<std::shared_ptr<Stream>>(store[streamKey].value)) {
        store[streamKey].value = std::make_shared<Stream>();
      }
      std::string newID = std::to_string(millisecondsTime)+'-'+std::to_string(sequenceNumber);
      auto& stream = *std::get<std::shared_ptr<Stream>>(store[streamKey].value);
      stream.push_back({newID, fieldValues});
      return '$'+newID;
    }
    else if (returnCode==1){
        return "-ERR The ID specified in XADD must be greater than 0-0";
    }
    else{
        return "-ERR The ID specified in XADD is equal or smaller than the target stream top item";
    }
}

Stream KeyValue::xrange(const std::string& streamKey, const std::string& start, const std::string& end) {
    std::lock_guard<std::mutex> lock(storeMutex);
    Stream result;

    std::string resolvedStart = (start == "-") ? "" : start;
    std::string resolvedEnd = (end == "+") ? std::to_string(std::numeric_limits<long long>::max()) + "-999999" : end;

    auto it = store.find(streamKey);
    if (it != store.end() && std::holds_alternative<std::shared_ptr<Stream>>(it->second.value)) {
        const Stream& entries = *std::get<std::shared_ptr<Stream>>(it->second.value);
        for (const auto& entry : entries) {
            if ((resolvedStart.empty() || entry.id >= resolvedStart) && (resolvedEnd.empty() || entry.id <= resolvedEnd)) {
                result.push_back(entry);
            }
        }
    }
    return result;
}

Stream KeyValue::xread(const std::string& streamKey) {
    std::lock_guard<std::mutex> lock(storeMutex);
    Stream result;

    auto it = store.find(streamKey);
    if (it != store.end() && std::holds_alternative<std::shared_ptr<Stream>>(it->second.value)) {
        const Stream& entries = *std::get<std::shared_ptr<Stream>>(it->second.value);
        for (const auto& entry : entries) {
            result.push_back(entry);
        }
    }
    return result;
}


std::string KeyValue::type(const std::string& key) {
    std::lock_guard<std::mutex> lock(storeMutex);
    auto it = store.find(key);
    if (it != store.end()) {
        if (std::holds_alternative<std::string>(it->second.value)) {
            return "string";
        } else if (std::holds_alternative<std::shared_ptr<Stream>>(it->second.value)) {
            return "stream";
        }
    }
    return "none";
}

