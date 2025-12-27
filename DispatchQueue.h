#ifndef PROJECT_DISPATCHQUEUE_H
#define PROJECT_DISPATCHQUEUE_H

#include <iostream>
#include "Order.h"
using namespace std;

struct NodeQueue {
    Order order;
    NodeQueue* next;
};

class DispatchQueue {
    NodeQueue* front;
    NodeQueue *rear;

public:
    DispatchQueue() {
        front = rear = nullptr;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(Order order) {
        NodeQueue* newNode = new NodeQueue();
        newNode->order = order;
        newNode->next = nullptr;

        if (isEmpty()) {
            front = rear = newNode;
            return;
        }

        rear->next = newNode;
        rear = newNode;
    }

    Order dequeue() {
        if (isEmpty()) {
            cout << "No Orders To Dispatch!" << endl;
            Order o;
            return o;
        }
        NodeQueue* temp = front;
        Order order = temp->order;
        front = front->next;
        delete temp;

        if (front == nullptr) {
            rear = nullptr;
        }

        return order;
    }

    void display() {
        if (isEmpty()) {
            cout << "No Orders To Dispatch!" << endl;
            return;
        }
        NodeQueue* temp = front;
        cout << "\n=========== TO DISPATCH ORDERS ===========\n";
        while (temp != nullptr) {
            cout << "Order ID : " << temp->order.orderId << "\n";
            cout << "Customer : " << temp->order.customerUsername << "\n";
            cout << "Items:\n";
            cout << "-----------------------------------------\n";
            temp->order.items.display();
            cout << endl;
            temp = temp->next;
        }
    }

    void clear() {
        while (!isEmpty()) {
            dequeue();   // dequeue already deletes nodes safely
        }
    }


};

#endif //PROJECT_DISPATCHQUEUE_H