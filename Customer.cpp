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
    char choice;
    while (true) {
        cout << "\n--------- CUSTOMER PORTAL ---------\n";
        cout << "1. Login\n";
        cout << "2. Signup\n";
        cout << "3. Exit\n";
        cout << "---------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == '1') login(ht, pBST, q, cartStack);
        else if (choice == '2') signup(ht, pBST, q, cartStack);
        else if (choice == '3') {
            cout << "\nExiting Customer Portal...\n";
            return;
        } else cout << "Invalid choice! Please try again.\n";
    }
}

void Customer::login(CustomerHashTable &ht, ProductBST &pBST, DispatchQueue &q, CartStack &cartStack) {
    string username, password;
    cout << "\n----------- LOGIN -----------\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    Customer *c = ht.search(username);
    if (c != nullptr && c->getPassword() == password) {
        cout << "\nLogin successful!\n";
        cout << "Welcome, " << username << "\n";
        pBST.displayPostorder();
        customerOptions(pBST, *c,q, cartStack);
    } else {
        cout << "\nInvalid username or password!\n";
    }
}

void Customer::signup(CustomerHashTable &ht, ProductBST &pBST,
                      DispatchQueue &q, CartStack &cartStack) {

    string username, password;
    cout << "\n----------- SIGNUP -----------\n";
    cout << "Choose username: ";
    cin >> username;
    cout << "Choose password: ";
    cin >> password;

    // Check if username already exists in hash table
    if (ht.search(username) != nullptr) {
        cout << "\nUsername already exists. Please try another.\n";
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

    cout << "\nSignup successful!\n";
    cout << "You can now login using your credentials.\n";

}

void Customer::viewProfile(Customer &customer) {
    ifstream file("data/orders.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open orders.txt\n";
        return;
    }

    cout << "\n=====================================\n";
    cout << "           CUSTOMER PROFILE\n";
    cout << "=====================================\n";
    cout << "Username: " << customer.getUsername() << "\n";


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
            cout << "\n-------------------------------------\n";
            cout << "Order ID : " << orderId << "\n";
            cout << "Status   : " << status << "\n";
            cout << "Items:\n";
            foundAnyOrder = true;
            lastOrderId = orderId;
        }

        cout << "  - " << pname << " | Quantity: " << qty << "\n";

    }

    if (!foundAnyOrder) {
        cout << "\nNo orders found for this account.\n";
    }

    cout << "\n============================\n";
    file.close();
}


void Customer::customerOptions(ProductBST &pBST, Customer &customer, DispatchQueue &q, CartStack &cartStack) {
    char choice;
    while (true) {
        cout << "\n----------- CUSTOMER MENU -----------\n";
        cout << "1. View Products\n";
        cout << "2. Sort Products by Price (Low → High)\n";
        cout << "3. Search Product\n";
        cout << "4. Add Product to Cart\n";
        cout << "5. Go to Cart\n";
        cout << "6. View Profile\n";
        cout << "7. Logout\n";
        cout << "------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                pBST.displayInorder();
                break;
            case '2':
                cout << "";
                break;
            case '3':
                cout << "";
                break;
            case '4':
                Cart::addProductToCart(pBST, cartStack, customer);
                break;
            case '5':
                Cart::cartOptions(pBST,cartStack, customer, q);
                break;
            case '6':
                viewProfile(customer);
                break;
            case '7':
                return;
            default:
                cout << "Invalid option! Please select again.\n";

        }
    }
}

