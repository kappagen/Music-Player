# Data Structures & Algorithms Implementation

## Overview
This Collaborative Music Playlist Manager implements multiple advanced DSA concepts for efficient playlist management, searching, and recommendation systems.


-================================================================================

## DSA Complexity Summary

| Data Structure |  Insert  |  Search  |  Delete  |  Space  |
|----------------|----------|----------|----------|---------|
| Linked List    |   O(n)   |   O(n)   |   O(n)   |   O(n)  |
| Stack          |   O(1)   |    -     |   O(1)   |   O(n)  |
| Queue          |   O(1)   |    -     |   O(1)   |   O(n)  |
| BST            | O(log n) | O(log n) | O(log n) |   O(n)  |
| Hash Table     |   O(1)   |   O(1)   |   O(1)   |   O(n)  |
| Max Heap       | O(log n) |   O(1)   | O(log n) |   O(n)  |
| Graph (BFS/DFS)|   O(1)   |  O(V+E)  |   O(1)   |  O(V+E) |

*Average case

-=================================================================================

## Features Demonstrating DSA

1. **Playlist Management**: Linked List
2. **Undo/Redo**: Stack
3. **Playback Queue**: Queue
4. **Fast Search**: BST + Hash Table
5. **Recommendations**: Graph (BFS/DFS)
6. **Top Songs**: Max Heap
7. **Sorting**: Multiple algorithms
8. **Concurrent Edits**: Thread Pool + Mutex

-===============================================================================

## 1. **Linked List** (Singly Linked List)
**File**: `Playlist.h`, `Playlist.cpp`

- **Purpose**: Core playlist storage using a singly linked list
- **Operations**:
  - Insert: O(n) - adds to end
  - Delete: O(n) - searches and removes
  - Search: O(n) - finds song by title
- **Features**: Dynamic memory management, efficient insertion/deletion

-================================================================================

## 2. **Stack** (LIFO - Last In First Out)
**File**: `QueueAndStack.h`

- **Purpose**: Undo/Redo functionality using stack
- **Operations**:
  - Push: O(1)
  - Pop: O(1)
  - Peek: O(1)
- **Implementation**: Template-based stack for type flexibility
- **Usage**: History management for collaborative editing

-=================================================================================

## 3. **Queue** (FIFO - First In First Out)
**File**: `QueueAndStack.h`

- **Purpose**: Playback queue management
- **Operations**:
  - Enqueue: O(1)
  - Dequeue: O(1)
  - Front: O(1)
- **Implementation**: Circular queue with linked list
- **Usage**: Sequential song playback

-================================================================================

## 4. **Binary Search Tree (BST)**
**File**: `BinarySearchTree.h`, `BinarySearchTree.cpp`

- **Purpose**: Fast song searching by title
- **Time Complexity**:
  - Insert: O(log n) average, O(n) worst
  - Search: O(log n) average, O(n) worst
  - Delete: O(log n) average, O(n) worst
- **Features**:
  - In-order traversal (sorted output)
  - Recursive insertion and deletion
  - Height calculation
- **Use Cases**: Quick song lookups, sorted display

-================================================================================

## 5. **Hash Table** (Separate Chaining)
**File**: `HashTable.h`, `HashTable.cpp`

- **Purpose**: O(1) average-case song lookups
- **Hash Function**: DJB2 algorithm (hash * 33 + c)
- **Collision Resolution**: Separate chaining with linked lists
- **Table Size**: 101 (prime number for better distribution)
- **Time Complexity**:
  - Insert: O(1) average
  - Search: O(1) average
  - Delete: O(1) average
- **Load Factor**: Monitored for performance
- **Use Cases**: Instant song retrieval by title

-================================================================================

## 6. **Graph** (Adjacency List)
**File**: `Graph.h`, `Graph.cpp`

- **Purpose**: Genre-based song recommendations
- **Representation**: Adjacency list using `map<string, vector<string>>`
- **Graph Type**: Undirected weighted graph
- **Algorithms Implemented**:
  - **BFS (Breadth-First Search)**: O(V + E)
    - Genre traversal
    - Recommendation generation
  - **DFS (Depth-First Search)**: O(V + E)
    - Genre exploration
    - Relationship discovery
- **Features**:
  - Genre relationship mapping
  - Related genre discovery
  - Recommendation system
- **Use Cases**: "Users who liked Rock also liked Metal"

-====================================================================================

## 7. **Max Heap** (Priority Queue)
**File**: `MaxHeap.h`, `MaxHeap.cpp`

- **Purpose**: Priority-based song queuing by rating
- **Type**: Max Heap (highest rating = highest priority)
- **Time Complexity**:
  - Insert: O(log n)
  - Extract Max: O(log n)
  - Peek Max: O(1)
- **Operations**:
  - Heapify Up: Maintains heap property after insertion
  - Heapify Down: Maintains heap property after extraction
- **Use Cases**:
  - Play highest-rated songs first
  - Top songs feature
  - Priority playlists

-====================================================================================

## 8. **Sorting Algorithms**
**File**: `SortingAlgorithms.h`, `SortingAlgorithms.cpp`

### Bubble Sort - O(n²)
- **Purpose**: Sort playlist by various attributes
- **Variants**:
  - Sort by Title (alphabetical)
  - Sort by Artist (alphabetical)
  - Sort by Rating (1-5)
  - Sort by Duration (seconds)
- **Implementation**: Optimized with early exit flag
- **Use Cases**: Small to medium playlists

-====================================================================================

## 9. **Searching Algorithms**

### Linear Search - O(n)
- **Implementation**: `Playlist::findSong()`
- **Purpose**: Find song by exact title match

### Binary Search - O(log n)
- **Implementation**: Via BST in-order traversal
- **Purpose**: Search in sorted data structures

-====================================================================================

## 10. **Thread Pool** (Concurrency)
**File**: `ThreadPool.h`, `ThreadPool.cpp`

- **Purpose**: Concurrent collaborative operations
- **Features**:
  - Worker thread management
  - Task queue
  - Thread-safe operations
- **Use Cases**: Simultaneous user edits

-===================================================================================

## Additional DSA Concepts

### 11. **Template Programming**
- Generic Stack and Queue implementations
- Type-safe data structures

### 12. **Memory Management**
- Dynamic allocation/deallocation
- Deep copy for undo/redo
- Destructor cleanup to prevent leaks

### 13. **Recursion**
- BST operations (insert, delete, search)
- DFS graph traversal
- Heap operations

### 14. **Hashing**
- Custom hash function implementation
- Collision handling

-==================================================================================