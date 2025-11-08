#include "BinarySearchTree.h"
#include <algorithm>

using namespace std;

BinarySearchTree::BinarySearchTree() : root(nullptr), size(0) {}

BinarySearchTree::~BinarySearchTree() {
    clear();
}

BinarySearchTree::BSTNode* BinarySearchTree::insertHelper(BSTNode* node, const Song& song) {
    if (node == nullptr) {
        size++;
        return new BSTNode(song);
    }
    
    if (song.getTitle() < node->data.getTitle()) {
        node->left = insertHelper(node->left, song);
    } else if (song.getTitle() > node->data.getTitle()) {
        node->right = insertHelper(node->right, song);
    } else {
        // Update existing song
        node->data = song;
    }
    
    return node;
}

void BinarySearchTree::insert(const Song& song) {
    root = insertHelper(root, song);
}

BinarySearchTree::BSTNode* BinarySearchTree::searchHelper(BSTNode* node, const string& title) {
    if (node == nullptr || node->data.getTitle() == title) {
        return node;
    }
    
    if (title < node->data.getTitle()) {
        return searchHelper(node->left, title);
    } else {
        return searchHelper(node->right, title);
    }
}

Song* BinarySearchTree::search(const string& title) {
    BSTNode* result = searchHelper(root, title);
    return result ? &(result->data) : nullptr;
}

BinarySearchTree::BSTNode* BinarySearchTree::findMin(BSTNode* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

BinarySearchTree::BSTNode* BinarySearchTree::deleteHelper(BSTNode* node, const string& title) {
    if (node == nullptr) {
        return nullptr;
    }
    
    if (title < node->data.getTitle()) {
        node->left = deleteHelper(node->left, title);
    } else if (title > node->data.getTitle()) {
        node->right = deleteHelper(node->right, title);
    } else {
        // Node found - delete it
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            size--;
            return nullptr;
        } else if (node->left == nullptr) {
            BSTNode* temp = node->right;
            delete node;
            size--;
            return temp;
        } else if (node->right == nullptr) {
            BSTNode* temp = node->left;
            delete node;
            size--;
            return temp;
        } else {
            // Node with two children
            BSTNode* minRight = findMin(node->right);
            node->data = minRight->data;
            node->right = deleteHelper(node->right, minRight->data.getTitle());
        }
    }
    
    return node;
}

bool BinarySearchTree::remove(const string& title) {
    int oldSize = size;
    root = deleteHelper(root, title);
    return size < oldSize;
}

void BinarySearchTree::inOrderHelper(BSTNode* node, vector<Song>& songs) {
    if (node == nullptr) return;
    
    inOrderHelper(node->left, songs);
    songs.push_back(node->data);
    inOrderHelper(node->right, songs);
}

vector<Song> BinarySearchTree::inOrderTraversal() {
    vector<Song> songs;
    inOrderHelper(root, songs);
    return songs;
}

void BinarySearchTree::clearHelper(BSTNode* node) {
    if (node == nullptr) return;
    
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
}

void BinarySearchTree::clear() {
    clearHelper(root);
    root = nullptr;
    size = 0;
}

int BinarySearchTree::heightHelper(BSTNode* node) {
    if (node == nullptr) return 0;
    
    int leftHeight = heightHelper(node->left);
    int rightHeight = heightHelper(node->right);
    
    return 1 + max(leftHeight, rightHeight);
}

int BinarySearchTree::getHeight() {
    return heightHelper(root);
}

int BinarySearchTree::getSize() const {
    return size;
}

bool BinarySearchTree::isEmpty() const {
    return root == nullptr;
}

void BinarySearchTree::buildFromVector(const vector<Song>& songs) {
    clear();
    for (const auto& song : songs) {
        insert(song);
    }
}
