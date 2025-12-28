#ifndef PROJECT_CUSTOMER_H
#define PROJECT_CUSTOMER_H

#include <string>

#include "CartStack.h"
#include "ProductBST.h"
#include "ProductPriceHeap.h"
class DispatchQueue;
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
    static void authenticationOptions(CustomerHashTable &ht, ProductBST &pBST, ProductPriceHeap &h, DispatchQueue &q, CartStack &cartStack);

    static void login(CustomerHashTable &ht, ProductBST &pBST, ProductPriceHeap &h, DispatchQueue &q, CartStack &cartStack);

    static void signup(CustomerHashTable &ht, ProductBST &pBST, ProductPriceHeap &h,  DispatchQueue &q, CartStack &cartStack);

    static void customerOptions(ProductBST &pBST, Customer &customer, ProductPriceHeap &h, DispatchQueue &q, CartStack &cartStack);

    static void viewProfile(Customer &customer);
};

#endif // PROJECT_CUSTOMER_H
