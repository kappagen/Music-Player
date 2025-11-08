#ifndef SORTINGALGORITHMS_H
#define SORTINGALGORITHMS_H

#include "Song.h"

/**
 * SortingAlgorithms provides manual sorting implementations for linked lists.
 * Uses bubble sort for simplicity, can be extended with other algorithms.
 */
class SortingAlgorithms {
public:
    struct Node {
        Song data;
        Node* next;
        Node(const Song& s) : data(s), next(nullptr) {}
    };
    
    /**
     * Bubble sort for linked list by title (ascending)
     * Time complexity: O(n^2)
     */
    static Node* bubbleSortByTitle(Node* head);
    
    /**
     * Bubble sort for linked list by artist (ascending)
     */
    static Node* bubbleSortByArtist(Node* head);
    
    /**
     * Bubble sort for linked list by rating (descending)
     */
    static Node* bubbleSortByRating(Node* head);
    
    /**
     * Bubble sort for linked list by duration (ascending)
     */
    static Node* bubbleSortByDuration(Node* head);

private:
    static int getLength(Node* head);
    static void swapNodeData(Node* a, Node* b);
};

#endif // SORTINGALGORITHMS_H