#include "Customer.h"
#include "CustomerHashTable.h"
#include "ProductBST.h"
#include <iostream>

#include "Cart.h"
#include "CartStack.h"
#include "DataLoader.h"
using namespace std;

void Customer::authenticationOptions(CustomerHashTable &ht, ProductBST &pBST) {
    int choice;
    while (true) {
        cout << "1. Login\n2. Signup\n3. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 1) login(ht, pBST);
        else if (choice == 2) signup(ht, pBST);
        else if (choice == 3) {
            cout << "Exiting...\n";
            return;
        } else cout << "Enter a valid choice!\n";
    }
}

void Customer::login(CustomerHashTable &ht, ProductBST &pBST) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    Customer *c = ht.search(username);
    if (c != nullptr && c->getPassword() == password) {
        cout << "Login successful! Welcome " << username << endl;
        pBST.displayPostorder();
        customerOptions(pBST, *c);
    } else {
        cout << "Invalid username or password.\n";
    }
}

void Customer::signup(CustomerHashTable &ht, ProductBST &pBST) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (ht.search(username) != nullptr) {
        cout << "Username already exists!\n";
        return;
    }

    Customer *c = new Customer(username, password, 0); // use pointer
    ht.insert(c); // insert pointer
    cout << "Signup successful! You can now login.\n";
}


void Customer::customerOptions(ProductBST &pBST, Customer &customer) {
    int choice;
    CartStack cartStack;
    while (true) {
        cout << "1. View Products" << endl;
        cout << "2. Sort Products by Price (Lowest to Highest)" << endl;
        cout << "3. Search Product" << endl;
        cout << "4. Add Product to Cart" << endl;
        cout << "5. Go to Cart" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                pBST.displayInorder();
                break;
            case 2:
                cout << "";
                break;
            case 3:
                cout << "";
                break;
            case 4:
                Cart::addProductToCart(pBST, cartStack, customer);
                break;
            case 5:
                Cart::cartOptions(cartStack, customer);
                break;
            case 6:
                return;
            default:
                cout << "Enter a valid Choice!" << endl;
        }
    }
}

