#ifndef PROJECT_PRODUCT_H
#define PROJECT_PRODUCT_H

#include <iostream>
using namespace std;

class Product {
public:
    int productId;
    string productName;
    float price;
    float rating;
    int stock;

    Product(){}

    Product(int product_id, const string &product_name, float product_price, float product_rating, int product_stock) {
        productId = product_id;
        productName = product_name;
        price = product_price;
        rating = product_rating;
        stock = product_stock;
    }

    static void viewAllProducts(Product &pBST);
    static void viewSortedProducts(Product &pBST);
    static void searchProduct(Product pBST);
};

#endif //PROJECT_PRODUCT_H