#ifndef PROJECT_CARTSTACK_H
#define PROJECT_CARTSTACK_H

#include "CartItem.h"

struct NodeStack {
    CartItem cartItem;
    NodeStack* next;
};

class CartStack {
    NodeStack* top;

public:
    CartStack() {
        top = nullptr;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void push(CartItem &cartItem) {
        NodeStack* newNode = new NodeStack();
        newNode->cartItem = cartItem;
        newNode->next = top;
        top = newNode;
        cout << "Product: " << cartItem.productName << " added to cart successfully!" << endl;
    }

    void pop() {
        if (isEmpty()) {
            return;
        }
        NodeStack* temp = top;
        top = top->next;
        delete temp;
    }

    CartItem peek() {
        if (isEmpty()) {
            CartItem c;
            return c;
        }
        return top->cartItem;
    }

    void display() {
        if (isEmpty()) {
            cout << "Cart is Empty!" << endl;
            return;
        }
        NodeStack* temp = top;
        cout << "Cart Items: " << endl;
        while (temp != nullptr) {
            cout << "Product ID: " << temp->cartItem.productId << endl;
            cout << "Product Name: " << temp->cartItem.productName;
            cout << "Quantity: " << temp->cartItem.quantity;
            cout << endl;
            temp = temp->next;
        }
    }
};

#endif //PROJECT_CARTSTACK_H