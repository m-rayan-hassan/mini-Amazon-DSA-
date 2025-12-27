#include <iostream>
#include "Customer.h"
#include "CustomerHashTable.h"
#include "Admin.h"
#include "ProductBST.h"
#include "DataLoader.h"
#include "DispatchQueue.h"
using namespace std;


int main() {
    char choice;
    CustomerHashTable ht;
    ProductBST pBST;
    DispatchQueue q;
    CartStack cartStack;
    DataLoader::loadCustomers(ht, "data/customers.txt");
    DataLoader:: loadProducts(pBST, "data/products.txt");
    cout << "=====================================\n";
    cout << "      WELCOME TO MINI AMAZON\n";
    cout << "=====================================\n\n";

    while (true) {
        cout << "\n----------- MAIN MENU -----------\n";
        cout << "1. Login as Customer\n";
        cout << "2. Login as Admin\n";
        cout << "3. Exit\n";
        cout << "--------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == '1') {
            Customer::authenticationOptions(ht, pBST, q, cartStack);
        } else if (choice == '2') {
            Admin:: login(pBST, q);
        } else if (choice == '3') {
            cout << "\nThank you for using Mini Amazon.\n";
            cout << "Goodbye!\n";
            return  0;
        } else {
            cout << "Enter a valid choice!" << endl;
        }
    }
}
