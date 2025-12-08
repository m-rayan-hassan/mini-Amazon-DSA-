#include "Cart.h"
#include "CartItem.h"
#include <iostream>

#include "CartStack.h"

using namespace std;


void Cart::addProductToCart(ProductBST &pBST, CartStack &cartStack) {
    int productId;
    int quantity;
    cout << "Enter Product ID to add to cart: ";
    cin >> productId;
    Node* product = pBST.search(productId);
    if (product == nullptr) {
        cout << "Product with product ID: " << productId << " not found" << endl;
        return;
    }
    if (product->data.stock <= 0) {
        cout << "Product: " << product->data.productName << " is out of stock" << endl;
        return;
    }
    cout << "Enter quantity: ";
    cin >> quantity;
    if (quantity <= 0 || quantity > product->data.stock) {
        cout << "Please enter valid quantity!" << endl;
        return;
    }

    CartItem cartItem(productId, product->data.productName, quantity);
    cartStack.push(cartItem);
}

void Cart::displayCart(CartStack &cartStack) {
    if (cartStack.isEmpty()) {

    }
    cartStack.display();
}

void Cart::cartOptions(CartStack &cartStack) {
    displayCart(cartStack);
    int choice;
    cout << "1. Delete/Undo last added product: (" << cartStack.peek().productName << ")" << endl;
    cout << "2. Checkout" << endl;
    cout << "3. Exit Cart" << endl;
    cout << "4. Exit" << endl;
    cin >> choice;
    switch (choice) {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        default:
            cout << "Enter a valid choice!" << endl;
            break;
    }

}
