#ifndef PROJECT_CARTSTACK_H
#define PROJECT_CARTSTACK_H

#include "CartItem.h"
#include <iostream>
#include <vector>
using namespace std;

struct NodeStack {
    CartItem cartItem;
    NodeStack* next;
};

class CartStack {
    NodeStack* top;

public:
    // Constructor
    CartStack() {
        top = nullptr;
    }

    // 🔴 DESTRUCTOR (VERY IMPORTANT)
    ~CartStack() {
        clear();
    }

    // 🔴 COPY CONSTRUCTOR (DEEP COPY)
    CartStack(const CartStack& other) {
        top = nullptr;

        if (other.top == nullptr) return;

        vector<CartItem> temp;
        NodeStack* curr = other.top;

        while (curr != nullptr) {
            temp.push_back(curr->cartItem);
            curr = curr->next;
        }

        // push back in reverse order
        for (int i = temp.size() - 1; i >= 0; i--) {
            push(temp[i]);
        }
    }

    // 🔴 COPY ASSIGNMENT OPERATOR (DEEP COPY)
    CartStack& operator=(const CartStack& other) {
        if (this == &other) return *this;

        clear();

        vector<CartItem> temp;
        NodeStack* curr = other.top;

        while (curr != nullptr) {
            temp.push_back(curr->cartItem);
            curr = curr->next;
        }

        for (int i = temp.size() - 1; i >= 0; i--) {
            push(temp[i]);
        }

        return *this;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(const CartItem &cartItem) {
        NodeStack* newNode = new NodeStack();
        newNode->cartItem = cartItem;
        newNode->next = top;
        top = newNode;
    }

    CartItem pop() {
        if (isEmpty()) {
            return CartItem(0, "", 0);
        }

        NodeStack* temp = top;
        CartItem item = temp->cartItem;

        top = top->next;
        delete temp;

        return item;
    }

    CartItem peek() const {
        if (isEmpty()) {
            return CartItem();
        }
        return top->cartItem;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    void display() const {
        if (isEmpty()) {
            cout << "Cart is Empty!" << endl;
            return;
        }

        NodeStack* temp = top;
        while (temp != nullptr) {
            cout << "Product ID: " << temp->cartItem.productId << endl;
            cout << "Product Name: " << temp->cartItem.productName << endl;
            cout << "Quantity: " << temp->cartItem.quantity << endl;
            cout << endl;
            temp = temp->next;
        }
    }
};

#endif // PROJECT_CARTSTACK_H
