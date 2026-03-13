#include "SLList.h"
#include <iostream>

template <typename T>
SLList<T>::SLList() {
    head = nullptr;
    tail = nullptr;
    listSize = 0;
};

template <typename T>
SLList<T>::~SLList() {
    clear();
};

template <typename T>
SLList<T>::SLList(const SLList<T>& other) {
    head = nullptr;
    tail = nullptr;
    listSize = 0;
    SLLNode<T>* cur = other.head;
    while (cur) {
        push_back(cur->data);
        cur = cur->next;
    }
};

template <typename T>
SLList<T>& SLList<T>::operator=(const SLList<T>& other) {
    clear();
    SLLNode<T>* cur = other.head;
    while (cur) {
        push_back(cur->data);
        cur = cur->next;
    }

    return *this;
};


template <typename T>
unsigned SLList<T>::size() const {
    return listSize;
};

template <typename T>
bool SLList<T>::empty() const {
    return (listSize == 0);
};

template <typename T>
void SLList<T>::push_front(const T& val) {
    head = new SLLNode<T>(val, head);

    //increment the list size
    listSize++;

    if (listSize == 1) {
        tail = head;
    }
};

template <typename T>
void SLList<T>::push_back(const T& val) {
    if (empty()) {
        head = new SLLNode<T>(val);
        tail = head;
    }
    else {
        tail->next = new SLLNode<T>(val); //add the node to the end
        tail = tail->next; //move the tail
    }

    //increment the list size
    listSize++;
};

template <typename T>
void SLList<T>::print() const {
    std::cout << "{ ";
    SLLNode<T>* cur = head;
    while (cur) {
        std::cout << cur->data;
        if (cur->next) {
            std::cout << " -> ";
        }
        cur = cur->next;
    }
    std::cout << " }\n";
};


template<typename T>
void SLList<T>::pop_front() {
    if (!empty()) {
        SLLNode<T>* to_delete = head;
        head = head->next;
        delete to_delete;
        listSize--;
        if (empty()) {
            tail = head;
        }
    }
};

template<typename T>
void SLList<T>::pop_back() {
    if (empty()) {
        return;
    }
    else if (size() == 1) {
        pop_front();
    }
    else {
        SLLNode<T>* to_delete = tail;
        SLLNode<T>* cur = head;
        //search second from the last node
        while (cur->next != tail) {
            cur = cur->next;
        }
        tail = cur;
        tail->next = nullptr;
        delete to_delete;
        listSize--;
    }
};


template<typename T>
void SLList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
};

template<typename T>
void SLList<T>::insert(unsigned pos, const T& value, unsigned n) {
    if (pos > listSize)
        return;
    for (unsigned j = 0; j < n; j++) {
        if (pos == 0) 
            push_front(value);
        else if (pos == listSize)
            push_back(value);
        else {
            SLLNode<T>* newNode = new SLLNode<T>(value); //Node being added
            SLLNode<T>* current = head; //Pointer to traverse the list
            for (unsigned i = 0; i < pos - 1; ++i)
                current = current->next; //Traverse the list until just before
                                         //the desired position
            newNode->next = current->next; //Sets the next of the new node to the node that
                                           //currently occupies 'pos'
            current->next = newNode; //Updates the next pointer of the node at pos - 1 to
                                     //point to the new node
            listSize++; //Incrememnt the list size
        }
    }
    return;

};

template<typename T>
void SLList<T>::erase(unsigned pos) { 
    if (pos >= listSize)
        return;
    if (pos == 0)
        pop_front();
    else if (pos == listSize - 1)
        pop_back();
    else {
        SLLNode<T>* current = head; //Pointer to traverse the list
        for (unsigned i = 0; i < pos - 1; ++i)
            current = current->next; //Traverse the list until just before
                                    //the desired position
        SLLNode<T>* temp = current->next; //Create a node at the position to be deleted
        current->next = temp->next; //Set pos - 1 next to point to pos + 1
        delete temp; //delete element at pos
        listSize--; //Decrement the list size
    }
    return;
};

template <typename T>
void SLList<T>::remove(const T& value) {
    SLLNode<T>* current = head; //Traverse the list
    SLLNode<T>* previous = nullptr;//Traverse the list
    while (current != nullptr) { //continues as long as there are nodes
        if (current->data == value) { //check for the value
            if (previous == nullptr) { //Case that the value removed is the ehad
                head = current->next;//Update head to point to the next node
                delete current;//Delete unwanted value
                current = head;//Move to the next node
            }
            else { //Case that the value to be removed is not the head
                previous->next = current->next; // Update the next pointer of the
                                                //prev node to skip current node
                delete current;//Delete the current node (unwanted value)
                current = previous->next;//Move to the next node
            }
            listSize--;//Decrement list Size
        }
        else { //continue checking the list if the value isnt found yet
            previous = current; //Move previous to the next node
            current = current->next;//Move current to the next node
        }
    }
}

template <typename T>
void SLList<T>::rotate_right(unsigned k) {
    if (empty() || k == 0)
        return; //Check for special Cases
    k = k % listSize; //Optimize k to ensure it isnt the list length 
    if (k == 0)       //Or a multiple of the list length
        return;

    SLLNode<T>* newTail = head;
    for (unsigned i = 1; i < listSize - k; i++)
        newTail = newTail->next; //Find location of the new tail
    SLLNode<T>* newHead = newTail->next;//Make new head the node after the new tail
    newTail->next = nullptr; //Make the next of the newTail a null pointer
    tail->next = head; //Make the old tail point to the old head
    head = newHead; //Update the head
    tail = newTail; //Update the tail
}
