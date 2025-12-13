#include "Customer.h"
#include "CustomerHashTable.h"
#include "ProductBST.h"
#include <iostream>

#include "Cart.h"
#include "CartStack.h"
#include "DataLoader.h"
#include "DispatchQueue.h"
using namespace std;

void Customer::authenticationOptions(CustomerHashTable &ht, ProductBST &pBST, DispatchQueue &q, CartStack &cartStack) {
    int choice;
    while (true) {
        cout << "1. Login\n2. Signup\n3. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 1) login(ht, pBST, q, cartStack);
        else if (choice == 2) signup(ht, pBST, q, cartStack);
        else if (choice == 3) {
            cout << "Exiting...\n";
            return;
        } else cout << "Enter a valid choice!\n";
    }
}

void Customer::login(CustomerHashTable &ht, ProductBST &pBST, DispatchQueue &q, CartStack &cartStack) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    Customer *c = ht.search(username);
    if (c != nullptr && c->getPassword() == password) {
        cout << "Login successful! Welcome " << username << endl;
        pBST.displayPostorder();
        customerOptions(pBST, *c,q, cartStack);
    } else {
        cout << "Invalid username or password.\n";
    }
}

void Customer::signup(CustomerHashTable &ht, ProductBST &pBST,
                      DispatchQueue &q, CartStack &cartStack) {

    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Check if username already exists in hash table
    if (ht.search(username) != nullptr) {
        cout << "Username already exists!\n";
        return;
    }

    int totalOrders = 0;

    // Insert into hash table
    Customer *c = new Customer(username, password, totalOrders);
    ht.insert(c);

    // Save to customers.txt
    ofstream out("data/customers.txt", ios::app);
    if (!out.is_open()) {
        cout << "Error: Could not open customers.txt\n";
        return;
    }

    out << username << " | "
        << password << " | "
        << totalOrders << endl;

    out.close();

    cout << "Signup successful! You can now login.\n";
}

void Customer::viewProfile(Customer &customer) {
    ifstream file("data/orders.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open orders.txt\n";
        return;
    }

    cout << "\n===== CUSTOMER PROFILE =====\n";
    cout << "Username: " << customer.getUsername() << endl;

    string line;
    getline(file, line); // skip header

    bool foundAnyOrder = false;
    int lastOrderId = -1;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string oidStr, username, pidStr, pname, qtyStr, status;

        getline(ss, oidStr, '|');
        getline(ss, username, '|');
        getline(ss, pidStr, '|');
        getline(ss, pname, '|');
        getline(ss, qtyStr, '|');
        getline(ss, status, '|');

        // trim helper
        auto trim = [](string &s) {
            while (!s.empty() && isspace(s.front())) s.erase(s.begin());
            while (!s.empty() && isspace(s.back())) s.pop_back();
        };

        trim(oidStr);
        trim(username);
        trim(pidStr);
        trim(pname);
        trim(qtyStr);
        trim(status);

        if (username != customer.getUsername())
            continue;

        int orderId = stoi(oidStr);
        int qty = stoi(qtyStr);

        // New Order
        if (orderId != lastOrderId) {
            cout << "\n----------------------------\n";
            cout << "Order ID: " << orderId << endl;
            cout << "Status  : " << status << endl;
            cout << "Items:\n";
            foundAnyOrder = true;
            lastOrderId = orderId;
        }

        cout << "  Product: " << pname
             << " | Qty: " << qty << endl;
    }

    if (!foundAnyOrder) {
        cout << "\nNo orders found.\n";
    }

    cout << "\n============================\n";
    file.close();
}


void Customer::customerOptions(ProductBST &pBST, Customer &customer, DispatchQueue &q, CartStack &cartStack) {
    int choice;
    while (true) {
        cout << "1. View Products" << endl;
        cout << "2. Sort Products by Price (Lowest to Highest)" << endl;
        cout << "3. Search Product" << endl;
        cout << "4. Add Product to Cart" << endl;
        cout << "5. Go to Cart" << endl;
        cout << "6. View Profile" << endl;
        cout << "7. Exit" << endl;
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
                Cart::cartOptions(pBST,cartStack, customer, q);
                break;
            case 6:
                viewProfile(customer);
                break;
            case 7:
                return;
            default:
                cout << "Enter a valid Choice!" << endl;
        }
    }
}

