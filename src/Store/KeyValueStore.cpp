#include "KeyValueStore.hpp"
#include<iostream>

void KeyValueStore::set(const std::string& key, const std::string& value, int ttl) {
    std::lock_guard<std::mutex> lock(storeMutex);
    auto now = std::chrono::steady_clock::now();
    auto expiry = now + std::chrono::seconds(ttl);
    auto now_duration = now.time_since_epoch();
    auto expiry_duration = expiry.time_since_epoch();

    // Convert durations to seconds for easier reading
    auto now_seconds = std::chrono::duration_cast<std::chrono::seconds>(now_duration).count();
    auto expiry_seconds = std::chrono::duration_cast<std::chrono::seconds>(expiry_duration).count();

    std::cout << "Current time: " << now_seconds << " seconds since epoch" << std::endl;
    std::cout << "Expiry time: " << expiry_seconds << " seconds since epoch" << std::endl;
    store[key] = {value, expiry};
    // Getting the key
    auto it = store.find(key);
    if (it != store.end()){
      std::cout << "It is found in key value store " << std:: endl;
      if(std::chrono::steady_clock::now() < it->second.second){
        std::cout << "****************" <<  it->second.first << std::endl;
      }else{
        std::cout << "Key is But the problem is the key is expired " << std:: endl;
      }
    }
    std::cout << "Key not found in key value store " << std:: endl;
    // std::cout << "Going to get the key from set " << key << std::endl;
    // std::string returned_value = KeyValueStore::get(key);
    // std::cout << "Returned value to set is " << returned_value << std::endl;
}

std::string KeyValueStore::get(const std::string& key) {
    std::lock_guard<std::mutex> lock(storeMutex);
    auto it = store.find(key);
    if (it != store.end()){
      std::cout << "It is found in key value store " << std:: endl;
      if(std::chrono::steady_clock::now() < it->second.second){
        std::cout << "But the problem is the key is expired " << std:: endl;
        return it->second.first;
      }
    }
    std::cout << "Key not found in key value store " << std:: endl;
    return "-1";
}

bool KeyValueStore::del(const std::string& key) {
    std::lock_guard<std::mutex> lock(storeMutex);
    bool erased = store.erase(key) > 0;
    if (erased) std::cout << "Key '" << key << "' deleted.\n";
    else std::cout << "Key '" << key << "' not found.\n";
    return erased;
}
