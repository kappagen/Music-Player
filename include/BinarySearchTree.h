#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "Song.h"
#include <vector>
#include <string>

using namespace std;

/**
 * Binary Search Tree for efficient song searching by title
 * Time Complexity: O(log n) average case, O(n) worst case
 * Space Complexity: O(n)
 */
class BinarySearchTree {
private:
    struct BSTNode {
        Song data;
        BSTNode* left;
        BSTNode* right;
        
        BSTNode(const Song& song) : data(song), left(nullptr), right(nullptr) {}
    };
    
    BSTNode* root;
    int size;
    
    // Helper functions
    BSTNode* insertHelper(BSTNode* node, const Song& song);
    BSTNode* searchHelper(BSTNode* node, const string& title);
    BSTNode* deleteHelper(BSTNode* node, const string& title);
    BSTNode* findMin(BSTNode* node);
    void inOrderHelper(BSTNode* node, vector<Song>& songs);
    void clearHelper(BSTNode* node);
    int heightHelper(BSTNode* node);
    
public:
    BinarySearchTree();
    ~BinarySearchTree();
    
    // Core operations
    void insert(const Song& song);
    Song* search(const string& title);
    bool remove(const string& title);
    
    // Traversal
    vector<Song> inOrderTraversal();
    
    // Utilities
    int getSize() const;
    int getHeight();
    bool isEmpty() const;
    void clear();
    
    // Build from vector
    void buildFromVector(const vector<Song>& songs);
};

#endif // BINARYSEARCHTREE_H
