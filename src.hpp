
#ifndef SRC_HPP
#define SRC_HPP

#include <cstdio>
#include <iostream>

using namespace std;

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        
        Node(const T& val) : data(val), next(nullptr), prev(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int listSize;
    
public:
    // Default constructor
    LinkedList() : head(nullptr), tail(nullptr), listSize(0) {}
    
    // Copy constructor
    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), listSize(0) {
        Node* current = other.head;
        while (current != nullptr) {
            pushBack(current->data);
            current = current->next;
        }
    }
    
    // Destructor
    virtual ~LinkedList() {
        while (head != nullptr) {
            popFront();
        }
    }
    
    // Insert at front
    void pushFront(const T& val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        listSize++;
    }
    
    // Insert at back
    void pushBack(const T& val) {
        Node* newNode = new Node(val);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        listSize++;
    }
    
    // Remove from front
    T popFront() {
        if (head == nullptr) {
            return T();
        }
        
        Node* temp = head;
        T result = temp->data;
        
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        
        delete temp;
        listSize--;
        return result;
    }
    
    // Remove from back
    T popBack() {
        if (tail == nullptr) {
            return T();
        }
        
        Node* temp = tail;
        T result = temp->data;
        
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        
        delete temp;
        listSize--;
        return result;
    }
    
    // Get size
    int size() const {
        return listSize;
    }
    
    // Print list
    void print() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " ";
            }
            current = current->next;
        }
        cout << endl;
    }
    
    // Virtual functions
    virtual const char* name() const {
        return "LinkedList";
    }
    
    virtual T peak() const {
        return T();
    }
    
    virtual T pop() {
        return T();
    }
    
    virtual void push(T val) {
        // Default implementation
    }
};

template<typename T>
class Stack : public LinkedList<T> {
public:
    virtual const char* name() const {
        return "Stack";
    }
    
    virtual T peak() const {
        // Stack top is the last element (back of list)
        // We need to access the private members, so we'll use the public interface
        Stack<T>* temp = const_cast<Stack<T>*>(this);
        LinkedList<T>* list = static_cast<LinkedList<T>*>(temp);
        
        // Create a copy to get the last element without modifying original
        LinkedList<T> copy(*list);
        return copy.popBack();
    }
    
    virtual T pop() {
        return this->popBack();
    }
    
    virtual void push(T val) {
        this->pushBack(val);
    }
};

template<typename T>
class Queue : public LinkedList<T> {
public:
    virtual const char* name() const {
        return "Queue";
    }
    
    virtual T peak() const {
        // Queue front is the first element (front of list)
        Queue<T>* temp = const_cast<Queue<T>*>(this);
        LinkedList<T>* list = static_cast<LinkedList<T>*>(temp);
        
        // Create a copy to get the first element without modifying original
        LinkedList<T> copy(*list);
        return copy.popFront();
    }
    
    virtual T pop() {
        return this->popFront();
    }
    
    virtual void push(T val) {
        this->pushBack(val);
    }
};

#endif
