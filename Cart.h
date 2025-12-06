#ifndef PROJECT_CART_H
#define PROJECT_CART_H

#include "CartStack.h"
#include "ProductBST.h"

class Cart {
public:
    static void addProductToCart(ProductBST &pBST, CartStack &cartStack);
    static void displayCart(CartStack &cartStack);
    static void cartOptions(CartStack &cartStack);
};

#endif //PROJECT_CART_H
