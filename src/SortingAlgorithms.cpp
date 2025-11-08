#include "SortingAlgorithms.h"

int SortingAlgorithms::getLength(Node* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

void SortingAlgorithms::swapNodeData(Node* a, Node* b) {
    Song temp = a->data;
    a->data = b->data;
    b->data = temp;
}

SortingAlgorithms::Node* SortingAlgorithms::bubbleSortByTitle(Node* head) {
    if (!head) return nullptr;
    
    int length = getLength(head);
    bool swapped;
    
    for (int i = 0; i < length - 1; i++) {
        swapped = false;
        Node* current = head;
        
        for (int j = 0; j < length - i - 1; j++) {
            if (current->next && current->data.getTitle() > current->next->data.getTitle()) {
                swapNodeData(current, current->next);
                swapped = true;
            }
            current = current->next;
        }
        
        if (!swapped) break;
    }
    
    return head;
}

SortingAlgorithms::Node* SortingAlgorithms::bubbleSortByArtist(Node* head) {
    if (!head) return nullptr;
    
    int length = getLength(head);
    bool swapped;
    
    for (int i = 0; i < length - 1; i++) {
        swapped = false;
        Node* current = head;
        
        for (int j = 0; j < length - i - 1; j++) {
            if (current->next && current->data.getArtist() > current->next->data.getArtist()) {
                swapNodeData(current, current->next);
                swapped = true;
            }
            current = current->next;
        }
        
        if (!swapped) break;
    }
    
    return head;
}

SortingAlgorithms::Node* SortingAlgorithms::bubbleSortByRating(Node* head) {
    if (!head) return nullptr;
    
    int length = getLength(head);
    bool swapped;
    
    for (int i = 0; i < length - 1; i++) {
        swapped = false;
        Node* current = head;
        
        for (int j = 0; j < length - i - 1; j++) {
            // Descending order for ratings
            if (current->next && current->data.getRating() < current->next->data.getRating()) {
                swapNodeData(current, current->next);
                swapped = true;
            }
            current = current->next;
        }
        
        if (!swapped) break;
    }
    
    return head;
}

SortingAlgorithms::Node* SortingAlgorithms::bubbleSortByDuration(Node* head) {
    if (!head) return nullptr;
    
    int length = getLength(head);
    bool swapped;
    
    for (int i = 0; i < length - 1; i++) {
        swapped = false;
        Node* current = head;
        
        for (int j = 0; j < length - i - 1; j++) {
            if (current->next && current->data.getDuration() > current->next->data.getDuration()) {
                swapNodeData(current, current->next);
                swapped = true;
            }
            current = current->next;
        }
        
        if (!swapped) break;
    }
    
    return head;
}