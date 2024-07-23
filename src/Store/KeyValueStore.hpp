#pragma once
#include <string>
#include <unordered_map>
#include <variant>
#include <optional>
#include <chrono>
#include <mutex>
#include <vector>
#include <memory>

struct StreamEntry {
    std::string id;
    std::unordered_map<std::string, std::string> fields;
};

using Stream = std::vector<StreamEntry>;
using Value = std::variant<std::string, std::shared_ptr<Stream>>;

struct TimedValue {
    Value value;
    std::optional<std::chrono::steady_clock::time_point> expiration;
};

class KeyValue {
public:
    void set(const std::string& key, const Value& value, const std::string& timeType, int ttl);
    void set(const std::string& key, const Value& value);
    Value get(const std::string& key);
    std::string type(const std::string& key);
    bool del(const std::string& key);
    void xadd(const std::string& streamKey, const std::string& id, const std::unordered_map<std::string, std::string>& fieldValues);
    Stream xrange(const std::string& streamKey, const std::string& start, const std::string& end);

private:
    std::mutex storeMutex;
    std::unordered_map<std::string, TimedValue> store;
};

class KeyValueStore {
public:
    static KeyValue& getInstance();

private:
    KeyValueStore() = default;
    static KeyValue instance;
};
