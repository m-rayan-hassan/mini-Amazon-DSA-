#ifndef PROJECT_ADMIN_H
#define PROJECT_ADMIN_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "DispatchQueue.h"
#include "ProductBST.h"
using namespace std;

class Admin {
private:
    string username;
    string password;

public:

    static void login(ProductBST &pBST, DispatchQueue &q);
    static void adminOptions(ProductBST &pBST, DispatchQueue &q);
    static void viewAllOrders();
};


#endif // PROJECT_ADMIN_H
