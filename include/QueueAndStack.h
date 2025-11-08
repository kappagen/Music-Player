#ifndef QUEUEANDSTACK_H
#define QUEUEANDSTACK_H

#include <stdexcept>

/**
 * Template-based custom Stack implementation for undo/redo operations.
 * Uses a singly linked list internally.
 */
template<typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    
    Node* top;
    int size;

public:
    Stack() : top(nullptr), size(0) {}
    
    ~Stack() {
        clear();
    }
    
    void push(const T& item) {
        Node* newNode = new Node(item);
        newNode->next = top;
        top = newNode;
        size++;
    }
    
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        Node* temp = top;
        T data = top->data;
        top = top->next;
        delete temp;
        size--;
        return data;
    }
    
    T& peek() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return top->data;
    }
    
    bool isEmpty() const {
        return top == nullptr;
    }
    
    int getSize() const {
        return size;
    }
    
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};

/**
 * Template-based custom Queue implementation (optional for future use).
 */
template<typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d) : data(d), next(nullptr) {}
    };
    
    Node* front;
    Node* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}
    
    ~Queue() {
        clear();
    }
    
    void enqueue(const T& item) {
        Node* newNode = new Node(item);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }
    
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        Node* temp = front;
        T data = front->data;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        size--;
        return data;
    }
    
    T& peek() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return front->data;
    }
    
    bool isEmpty() const {
        return front == nullptr;
    }
    
    int getSize() const {
        return size;
    }
    
    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

#endif // QUEUEANDSTACK_H