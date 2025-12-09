#include "Cart.h"
#include "CartItem.h"
#include "CartStack.h"
#include "Customer.h"
#include "ProductBST.h"
#include <iostream>

using namespace std;

// Add product to cart
void Cart::addProductToCart(ProductBST &pBST, CartStack &cartStack, Customer &customer) {
    int productId, quantity;

    cout << "Enter Product ID to add to cart: ";
    cin >> productId;

    Node* product = pBST.search(productId);  // Search in BST
    if (product == nullptr) {
        cout << "Product with product ID " << productId << " not found!" << endl;
        return;
    }

    if (product->data.stock <= 0) {
        cout << "Product: " << product->data.productName << " is out of stock!" << endl;
        return;
    }

    cout << "Enter quantity: ";
    cin >> quantity;
    if (quantity <= 0 || quantity > product->data.stock) {
        cout << "Invalid quantity! Available stock: " << product->data.stock << endl;
        return;
    }


    CartItem cartItem(productId, product->data.productName, quantity);
    cartStack.push(cartItem);
    cout << quantity << " x " << product->data.productName << " added to cart." << endl;
}
void Cart::displayCart(CartStack &cartStack, Customer &customer) {
    if (cartStack.isEmpty()) {
        cout << "Cart is empty!" << endl;
        return;
    }
    cout << "\n------ CART ITEMS ------" << endl;
    cartStack.display();
}

// Cart menu options
void Cart::cartOptions(CartStack &cartStack, Customer &customer) {
    int choice;

    do {
        cout << "\n------ CART MENU ------\n";
        displayCart(cartStack, customer);

        if (!cartStack.isEmpty()) {
            cout << "1. Delete/Undo last added product: ("
                 << cartStack.peek().productName << ")" << endl;
        } else {
            cout << "1. Delete/Undo last added product" << endl;
        }

        cout << "2. Checkout" << endl;
        cout << "3. Exit Cart" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (cartStack.isEmpty()) {
                    cout << "Cart is already empty!" << endl;
                } else {
                    cout << "Removed product: "
                         << cartStack.peek().productName << endl;
                    cartStack.pop();
                }
                break;

            case 2:
                if (cartStack.isEmpty()) {
                    cout << "Cart is empty! Nothing to checkout." << endl;
                } else {
                    cout << "Checkout completed successfully!" << endl;
                    while (!cartStack.isEmpty()) {
                        cartStack.pop(); // Clear cart
                    }
                }
                break;

            case 3:
                cout << "Exiting cart menu..." << endl;
                break;

            default:
                cout << "Enter a valid choice!" << endl;
                break;
        }

    } while (choice != 3);
}
