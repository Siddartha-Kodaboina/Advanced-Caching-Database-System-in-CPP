#include "KeyValueStore.hpp"
#include "../Utils/utils.hpp"
#include <iostream>

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

void KeyValue::xadd(const std::string& streamKey, const std::string& id, const std::unordered_map<std::string, std::string>& fieldValues) {
    std::lock_guard<std::mutex> lock(storeMutex);
    if (!store.count(streamKey) || !std::holds_alternative<std::shared_ptr<Stream>>(store[streamKey].value)) {
        store[streamKey].value = std::make_shared<Stream>();
    }
    auto& stream = *std::get<std::shared_ptr<Stream>>(store[streamKey].value);
    stream.push_back({id, fieldValues});
}

Stream KeyValue::xrange(const std::string& streamKey, const std::string& start, const std::string& end) {
    std::lock_guard<std::mutex> lock(storeMutex);
    Stream result;
    auto it = store.find(streamKey);
    if (it != store.end() && std::holds_alternative<std::shared_ptr<Stream>>(it->second.value)) {
        const Stream& entries = *std::get<std::shared_ptr<Stream>>(it->second.value);
        for (const auto& entry : entries) {
            if ((start == "-" || entry.id >= start) && (end == "+" || entry.id <= end)) {
                result.push_back(entry);
            }
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

