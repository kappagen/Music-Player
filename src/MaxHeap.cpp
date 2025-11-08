#include "MaxHeap.h"
#include <stdexcept>

using namespace std;

MaxHeap::MaxHeap() {}

void MaxHeap::heapifyUp(int index) {
    if (index == 0) return;
    
    int parentIdx = parent(index);
    
    // Compare by rating (higher rating = higher priority)
    if (heap[index].getRating() > heap[parentIdx].getRating()) {
        swap(heap[index], heap[parentIdx]);
        heapifyUp(parentIdx);
    }
}

void MaxHeap::heapifyDown(int index) {
    int largest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    
    if (left < (int)heap.size() && heap[left].getRating() > heap[largest].getRating()) {
        largest = left;
    }
    
    if (right < (int)heap.size() && heap[right].getRating() > heap[largest].getRating()) {
        largest = right;
    }
    
    if (largest != index) {
        swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}

void MaxHeap::insert(const Song& song) {
    heap.push_back(song);
    heapifyUp(heap.size() - 1);
}

Song MaxHeap::extractMax() {
    if (isEmpty()) {
        throw runtime_error("Heap is empty");
    }
    
    Song maxSong = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    
    if (!isEmpty()) {
        heapifyDown(0);
    }
    
    return maxSong;
}

Song MaxHeap::peekMax() const {
    if (isEmpty()) {
        throw runtime_error("Heap is empty");
    }
    return heap[0];
}

int MaxHeap::getSize() const {
    return heap.size();
}

bool MaxHeap::isEmpty() const {
    return heap.empty();
}

void MaxHeap::clear() {
    heap.clear();
}

vector<Song> MaxHeap::getAllSongs() const {
    return heap;
}

void MaxHeap::buildHeap(const vector<Song>& songs) {
    clear();
    for (const auto& song : songs) {
        insert(song);
    }
}
