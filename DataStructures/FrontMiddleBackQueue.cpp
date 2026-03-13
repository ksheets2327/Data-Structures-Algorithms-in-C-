#include <iostream>
#include <cmath>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node(int x) {
        val = x;
        next = NULL;
    }
};

class FrontMiddleBackQueue {
public:
    Node* front, * back;
    int size = 0;
    FrontMiddleBackQueue() {};

    void pushFront(int val) {
        Node* newNode = new Node(val);
        if (size == 0)
            front = back = newNode;
        else {
            newNode->next = front;
            front = newNode;
        }
        size++;
    };

    void pushMiddle(int val) {
        if (size == 0 || size == 1) {
            pushFront(val);
            return;
        }
        int middle = size / 2;
        Node* temp = front;
        for (int i = 0; i < middle - 1; ++i)
            temp = temp->next;
        Node* newNode = new Node(val);
        newNode->next = temp->next;
        temp->next = newNode;
        size++;
    };

    void pushBack(int val) {
        Node* newNode = new Node(val);
        if (size == 0)
            front = back = newNode;
        else {
            back->next = newNode;
            back = newNode;
        }
        size++;
    };

    int popFront() {
        if (size == 0)
            return -1;
        int val = front->val;
        Node* temp = front;
        front = front->next;
        delete temp;
        size--;
        return val;
    };

    int popMiddle() {
        if (size == 0)
            return -1;

        Node* prev = nullptr;
        Node* slow = front;
        Node* fast = front;

        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            prev = slow;
            slow = slow->next;
        }

        int val;
        if (fast == nullptr) { // Even number of elements
            val = prev->val;
            prev->next = slow->next;
        }
        else { // Odd number of elements
            val = slow->val;
            if (prev != nullptr)
                prev->next = slow->next;
            else
                front = slow->next;
        }

        delete slow;
        size--;
        return val;
    };


    int popBack() {
        if (size == 0)
            return -1;

        int val = back->val;
        if (size == 1) {
            delete back;
            front = back = nullptr;
        }
        else {
            Node* temp = front;
            while (temp->next != back)
                temp = temp->next;
            delete back;
            back = temp;
            back->next = nullptr;
        }
        size--;
        return val;
    };

    void reverse() {
        if (size <= 1)
            return;
        Node* prev = NULL;
        Node* current = front;
        Node* nextNode;
        while (current != NULL) {
            nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }
        front = prev;
    };
};

int main() {
    FrontMiddleBackQueue q;
    // Test case 1: Pushing elements to the front, middle, and back of the queue
    q.pushFront(1); // 1
    q.pushMiddle(2); // 2 1
    q.pushBack(3); // 2 1 3
    q.pushMiddle(4); // 2 4 1 3
    q.pushMiddle(5); // 2 4 5 1 3
    q.pushFront(6); // 6 2 4 5 1 3
    // Expected output: 6 2 4 5 1 3

    Node* temp = q.front;
    while (temp) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;

    // Test case 2: Popping elements from the front, middle, and back of the queue
    cout << q.popFront() << endl; // Expected output: 6
    cout << q.popMiddle() << endl; // Expected output: 5
    cout << q.popBack() << endl; // Expected output: 3
    cout << q.popMiddle() << endl; // Expected output: 4
    // Expected output after popping: 2 1
    temp = q.front;
    while (temp) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;
    // Edge case: Popping elements from an empty queue
    FrontMiddleBackQueue q2;
    cout << q2.popFront() << endl; // Expected output: -1
    cout << q2.popMiddle() << endl; // Expected output: -1
    cout << q2.popBack() << endl; // Expected output: -1
    // Edge case: Popping elements from a queue of size 1
    FrontMiddleBackQueue q3;
    q3.pushFront(1);
    cout << q3.popFront() << endl; // Expected output: 1
    q3.pushFront(1);
    cout << q3.popMiddle() << endl; // Expected output: 1
    q3.pushFront(1);
    cout << q3.popBack() << endl; // Expected output: 1
    FrontMiddleBackQueue q4;
    // Test case 3: reversing the queue
    q4.pushFront(1);
    q4.pushFront(2);
    q4.pushFront(3);
    q4.pushFront(4);
    q4.reverse();
    temp = q4.front;
    while (temp) {
        cout << temp->val << " ";
        temp = temp->next;
    }

    cout << endl;
    return 0;
};
