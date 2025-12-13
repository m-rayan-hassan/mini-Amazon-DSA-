#include <iostream>
#include "Customer.h"
#include "CustomerHashTable.h"
#include "Admin.h"
#include "ProductBST.h"
#include "DataLoader.h"
#include "DispatchQueue.h"
using namespace std;


int main() {
    int choice;
    CustomerHashTable ht;
    ProductBST pBST;
    DispatchQueue q;
    CartStack cartStack;
    DataLoader::loadCustomers(ht, "data/customers.txt");
    DataLoader:: loadProducts(pBST, "data/products.txt");
    cout << "----- WELCOME TO MINI AMAZON -----" << endl;
    cout << "\n";
    while (true) {
        cout << "1. I am Customer: " << endl;
        cout << "2. I am Admin: " << endl;
        cout << "3. Exit" << endl;
        cout << "Enter Choice: ";
        cin >> choice;
        if (choice == 1) {
            Customer::authenticationOptions(ht, pBST, q, cartStack);
        } else if (choice == 2) {
            Admin:: login(pBST, q);
        } else if (choice == 3) {
            cout << "Exiting..." << endl;
            return  0;
        } else {
            cout << "Enter a valid choice!" << endl;
        }
    }
}
