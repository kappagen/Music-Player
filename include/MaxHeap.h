#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "Song.h"
#include <vector>

using namespace std;

/**
 * Max Heap (Priority Queue) for songs based on rating
 * Higher rated songs have higher priority
 * Time Complexity: O(log n) for insert and extract
 * Space Complexity: O(n)
 */
class MaxHeap {
private:
    vector<Song> heap;
    
    // Helper functions
    int parent(int i) const { return (i - 1) / 2; }
    int leftChild(int i) const { return 2 * i + 1; }
    int rightChild(int i) const { return 2 * i + 2; }
    
    void heapifyUp(int index);
    void heapifyDown(int index);
    
public:
    MaxHeap();
    
    // Core operations
    void insert(const Song& song);
    Song extractMax();
    Song peekMax() const;
    
    // Utilities
    int getSize() const;
    bool isEmpty() const;
    void clear();
    
    // Get all songs in heap order
    vector<Song> getAllSongs() const;
    
    // Build heap from vector
    void buildHeap(const vector<Song>& songs);
};

#endif // MAXHEAP_H
