#ifndef PROJECT_CART_H
#define PROJECT_CART_H

#include "CartStack.h"
#include "Customer.h"
#include "ProductBST.h"

class Cart {
public:
    static void addProductToCart(ProductBST &pBST, CartStack &cartStack, Customer &customer);
    static void displayCart(CartStack &cartStack, Customer &customer);
    static void cartOptions(ProductBST &pBST, CartStack &cartStack, Customer &customer, DispatchQueue &q);
};

#endif //PROJECT_CART_H
