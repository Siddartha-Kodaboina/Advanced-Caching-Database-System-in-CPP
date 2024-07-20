#pragma once
#include <string>
#include <unordered_map>
#include <chrono>
#include <mutex>

class KeyValueStore {
public:
    using ValueWithExpiry = std::pair<std::string, std::chrono::steady_clock::time_point>;
private:
    std::unordered_map<std::string, ValueWithExpiry> store;
    std::mutex storeMutex; // For thread-safety

public:
    void set(const std::string& key, const std::string& value, int ttl);
    std::string get(const std::string& key);
    bool del(const std::string& key);
    // Additional methods for other commands
};
