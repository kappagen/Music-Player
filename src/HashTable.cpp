#include "HashTable.h"

using namespace std;

HashTable::HashTable() : table(TABLE_SIZE), size(0) {}

int HashTable::hashFunction(const string& key) const {
    unsigned long hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % TABLE_SIZE;
}

void HashTable::insert(const string& key, const Song& song) {
    int index = hashFunction(key);
    
    // Check if key already exists
    for (auto& node : table[index]) {
        if (node.key == key) {
            node.value = song; // Update existing
            return;
        }
    }
    
    // Insert new node
    table[index].push_back(HashNode(key, song));
    size++;
}

Song* HashTable::search(const string& key) {
    int index = hashFunction(key);
    
    for (auto& node : table[index]) {
        if (node.key == key) {
            return &(node.value);
        }
    }
    
    return nullptr;
}

bool HashTable::remove(const string& key) {
    int index = hashFunction(key);
    
    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->key == key) {
            table[index].erase(it);
            size--;
            return true;
        }
    }
    
    return false;
}

int HashTable::getSize() const {
    return size;
}

bool HashTable::isEmpty() const {
    return size == 0;
}

void HashTable::clear() {
    for (auto& bucket : table) {
        bucket.clear();
    }
    size = 0;
}

double HashTable::getLoadFactor() const {
    return static_cast<double>(size) / TABLE_SIZE;
}

vector<Song> HashTable::getAllSongs() const {
    vector<Song> songs;
    for (const auto& bucket : table) {
        for (const auto& node : bucket) {
            songs.push_back(node.value);
        }
    }
    return songs;
}
