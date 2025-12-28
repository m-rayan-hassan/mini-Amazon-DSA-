#include "Cart.h"
#include "CartItem.h"
#include "CartStack.h"
#include "Customer.h"
#include "ProductBST.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "DispatchQueue.h"
#include "Order.h"

using namespace std;

static const string CART_FILE = "data/Cart.txt";

void loadCartFromFile(CartStack &cartStack, const string &username) {
    ifstream file(CART_FILE);
    if (!file.is_open()) return;

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string user, idStr, name, qtyStr;

        getline(ss, user, '|');
        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, qtyStr, '|');

        auto trim = [](string &s) {
            while (!s.empty() && s.front() == ' ') s.erase(0, 1);
            while (!s.empty() && (s.back() == ' ' || s.back()=='\r')) s.pop_back();
        };

        trim(user); trim(idStr); trim(name); trim(qtyStr);

        if (user == username) {
            CartItem item(stoi(idStr), name, stoi(qtyStr));
            cartStack.push(item);
        }
    }

    file.close();
}

void saveCartToFile(CartStack &cartStack, const string &username) {
    ifstream inFile(CART_FILE);
    vector<string> allLines;

    string line;
    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            if (line.find(username + " |") != 0) {
                allLines.push_back(line);
            }
        }
        inFile.close();
    }

    ofstream outFile(CART_FILE, ios::trunc);
    if (!outFile.is_open()) return;

    // Write other users' data back
    for (const string &l : allLines) {
        outFile << l << endl;
    }

    CartStack auxStack;

    while (!cartStack.isEmpty()) {
        CartItem item = cartStack.peek();

        outFile << username << " | "
                << item.productId << " | "
                << item.productName << " | "
                << item.quantity << endl;

        auxStack.push(cartStack.pop());
    }

    while (!auxStack.isEmpty()) {
        cartStack.push(auxStack.pop());
    }

    outFile.close();
}



void Cart::addProductToCart(ProductBST &pBST, CartStack &cartStack, Customer &customer) {
    int productId, quantity;

    cout << "Enter Product ID to add to cart: ";
    cin >> productId;

    Node* product = pBST.search(productId);
    if (product == nullptr) {
        cout << "Product not found!" << endl;
        return;
    }

    if (product->data.stock <= 0) {
        cout << product->data.productName << " is out of stock!" << endl;
        return;
    }

    cout << "Enter quantity: ";
    cin >> quantity;

    if (quantity <= 0 || quantity > product->data.stock) {
        cout << "Invalid quantity! Available stock: "
             << product->data.stock << endl;
        return;
    }

    CartItem item(productId, product->data.productName, quantity);
    cartStack.push(item);
    pBST.searchAndUpdateQuantity(cartStack.peek().productId, cartStack.peek().quantity, "add");
    saveCartToFile(cartStack, customer.getUsername());
    cout << "Added " << product->data.productName << " to cart successfully.\n";
}

void Cart::displayCart(CartStack &cartStack, Customer &customer) {
    cout << "\n------ CART ITEMS ------\n";
    cartStack.display();
}

void Cart::cartOptions(ProductBST &pBST, CartStack &cartStack, Customer &customer, DispatchQueue &q) {
    char choice;

    if (cartStack.isEmpty()) {
        loadCartFromFile(cartStack, customer.getUsername());
    }

    do {
        cout << "\n=========== YOUR CART ===========\n";

        cout << "\n----------- CART MENU -----------\n";
        displayCart(cartStack, customer);

        if (!cartStack.isEmpty()) {
            cout << "1. Delete/Undo last added product ("
                 << cartStack.peek().productName << ")\n";
        } else {
            cout << "1. Delete/Undo last added product\n";
        }

        cout << "2. Checkout\n";
        cout << "3. Exit Cart\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                if (cartStack.isEmpty()) {
                    cout << "\nCart is empty!\n";
                } else {
                    cout << "\nRemoved: " << cartStack.peek().productName << endl;
                    pBST.searchAndUpdateQuantity(cartStack.peek().productId, cartStack.peek().quantity, "undo");
                    cartStack.pop();
                    saveCartToFile(cartStack, customer.getUsername());
                }
                break;

             case '2':
                if (cartStack.isEmpty()) {
                    cout << "Nothing to checkout!\n";
                } else {
                    cout << "Select Address: " << endl;
                    cout << "1. Islamabad\n"
                         << "2. Rawalpindi\n"
                         << "3. Lahore\n"
                         << "4. Karachi\n"
                         << "5. Quetta\n"
                         << "6. Peshawar\n"
                         << "7. Faisalabad\n"
                         << "8. Multan\n"
                         << "9. Gujranwala\n"
                         << "10. Sialkot\n"
                         << "11. Hyderabad\n"
                         << "12. Sukkur\n"
                         << "13. Bahawalpur\n"
                         << "14. Abbottabad\n"
                         << "15. Sargodha\n"
                         << "16. Mirpur\n"
                         << "17. Muzaffarabad\n"
                         << "18. Gwadar\n";
                    cout << endl;

                    srand(time(0));
                    int orderId = rand() % 900000 + 100000;
                    Order order(orderId, customer.getUsername(), cartStack);
                    q.enqueue(order);

                    ofstream out("data/orders.txt", ios::app);
                    if (!out.is_open()) {
                        cout << "Error: Could not open orders.txt to save order.\n";
                    } else {
                        CartStack tempStack;

                        while (!cartStack.isEmpty()) {
                            CartItem item = cartStack.peek();
                            out << orderId << " | " << customer.getUsername() << " | "
                                << item.productId << " | " << item.productName << " | "
                                << item.quantity << " | To Dispatch\n";

                            tempStack.push(item);
                            cartStack.pop();
                        }

                        out.close();
                    }

                    cout << "\n=====================================\n";
                    cout << "      ORDER PLACED SUCCESSFULLY\n";
                    cout << "=====================================\n";
                    cout << "Your order has been placed and will be dispatched soon.\n";

                    // Ensure cart is empty after checkout
                    while (!cartStack.isEmpty()) {
                        cartStack.pop();
                    }
                    saveCartToFile(cartStack, customer.getUsername());
                }
                break;


            case '3':
                cout << "Exiting cart...\n";
                return;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 3);
}
