#include "KeyValueStore.hpp"
#include "../Utils/utils.hpp"
#include<iostream>

void KeyValueStore::set(const std::string& key, const std::string& value) {
  std::lock_guard<std::mutex> lock(storeMutex);
  store[key] = std::make_pair(value, std::nullopt);
}
void KeyValueStore::set(const std::string& key, const std::string& value, const std::string& timeType, int ttl) {
  std::lock_guard<std::mutex> lock(storeMutex);
  if(utils::toLowerCase(timeType)=="ex"){
    ttl = ttl * 1000;
  }
  
  auto expiry = std::chrono::steady_clock::now() + std::chrono::milliseconds(ttl);
  store[key] = std::make_pair(value, expiry);
}

std::string KeyValueStore::get(const std::string& key) {
  std::lock_guard<std::mutex> lock(storeMutex);
  auto it = store.find(key);
  if (it != store.end()) {
    std::cout << "It is found in key value store." << std::endl;
    if (!it->second.second || std::chrono::steady_clock::now() < it->second.second.value()) {
      return it->second.first;
    } else {
      std::cout << "But the key is expired." << std::endl;
    }
  }
  std::cout << "Key not found in key value store." << std::endl;
  return "";
}

bool KeyValueStore::del(const std::string& key) {
  std::lock_guard<std::mutex> lock(storeMutex);
  bool erased = store.erase(key) > 0;
  if (erased) std::cout << "Key '" << key << "' deleted.\n";
  else std::cout << "Key '" << key << "' not found.\n";
  return erased;
}
