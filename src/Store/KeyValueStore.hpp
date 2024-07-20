#pragma once
#include <mutex>
#include <unordered_map>
#include <chrono>

class KeyValueStore {
public:
    static KeyValueStore& getInstance();

    void set(const std::string& key, const std::string& value, const std::string& timeType, int ttl);
    void set(const std::string& key, const std::string& value);
    std::string get(const std::string& key);
    bool del(const std::string& key);

private:
    KeyValueStore() {}  // Private constructor
    std::mutex storeMutex;
    std::unordered_map<std::string, std::pair<std::string, std::optional<std::chrono::steady_clock::time_point>>> store;
};

inline KeyValueStore& KeyValueStore::getInstance() {
    static KeyValueStore instance;
    return instance;
}
