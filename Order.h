#ifndef PROJECT_ORDER_H
#define PROJECT_ORDER_H

#include <iostream>

#include "CartStack.h"
#include "Customer.h"
using namespace std;

class Order {
public:
    int orderId;
    string customerUsername;
    CartStack items;
    string status;
};



#endif //PROJECT_ORDER_H