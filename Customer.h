#ifndef PROJECT_CUSTOMER_H
#define PROJECT_CUSTOMER_H

#include <string>
#include "ProductBST.h"
using namespace std;

class CustomerHashTable; // forward declaration

class Customer {
private:
    string username;
    string password;
    int totalOrders;

public:
    Customer() {
    }
    Customer(string u, string p, int orders = 0) {
        username = u;
        password = p;
        totalOrders = orders;
    }

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    int getOrders() const { return totalOrders; }

    // ------------------- Authentication -------------------
    static void authenticationOptions(CustomerHashTable &ht, ProductBST &pBST);

    static void login(CustomerHashTable &ht, ProductBST &pBST);

    static void signup(CustomerHashTable &ht, ProductBST &pBST);

    static void customerOptions(ProductBST &pBST);


};

#endif // PROJECT_CUSTOMER_H
