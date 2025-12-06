#ifndef PROJECT_CART_ITEM_H
#define PROJECT_CART_ITEM_H

#include "ProductBST.h"
using namespace std;

class CartItem {
public:
    int productId;
    string productName;
    int quantity;

    CartItem(){}
    CartItem(int product_id, string product_name, int product_quantity) {
        productId = product_id;
        productName = product_name;
        quantity = product_quantity;
    }
};

#endif //PROJECT_CART_H