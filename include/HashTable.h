#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Song.h"
#include <vector>
#include <string>
#include <list>

using namespace std;

/**
 * Hash Table using separate chaining for collision resolution
 * Time Complexity: O(1) average case for insert, search, delete
 * Space Complexity: O(n)
 */
class HashTable {
private:
    static const int TABLE_SIZE = 101; // Prime number for better distribution
    
    struct HashNode {
        string key;
        Song value;
        
        HashNode(const string& k, const Song& v) : key(k), value(v) {}
    };
    
    vector<list<HashNode>> table;
    int size;
    
    // Hash function
    int hashFunction(const string& key) const;
    
public:
    HashTable();
    
    // Core operations
    void insert(const string& key, const Song& song);
    Song* search(const string& key);
    bool remove(const string& key);
    
    // Utilities
    int getSize() const;
    bool isEmpty() const;
    void clear();
    double getLoadFactor() const;
    
    // Get all songs
    vector<Song> getAllSongs() const;
};

#endif // HASHTABLE_H
