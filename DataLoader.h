#ifndef PROJECT_DATALOADER_H
#define PROJECT_DATALOADER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include "Customer.h"
#include "CustomerHashTable.h"
#include "Product.h"

using namespace std;

class DataLoader {
public:
    static void loadCustomers(CustomerHashTable &ht, const string &filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open " << filename << endl;
            return;
        }

        string line;
        getline(file, line); // skip heading line

        while (getline(file, line)) {
            stringstream ss(line);
            string id, username, password, orders;
            getline(ss, id, '|');
            getline(ss, username, '|');
            getline(ss, password, '|');
            getline(ss, orders, '|');

            auto trim = [](string &s){
                while (!s.empty() && (s[0]==' ')) s.erase(0,1);
                while (!s.empty() && (s.back()==' ' || s.back()=='\r' || s.back()=='\n')) s.pop_back();
            };

            trim(username); trim(password); trim(orders);

            Customer *c = new Customer(username, password, stoi(orders));
            ht.insert(c);
        }

        file.close();
        cout << "Customers loaded successfully.\n";
    }

    static void loadProducts(ProductBST &bst, const string &filename = "data/products.txt") {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open " << filename << endl;
            return;
        }

        string line;
        getline(file, line); // skip heading

        while (getline(file, line)) {
            stringstream ss(line);
            string id, name, price, rating, stock;

            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, price, '|');
            getline(ss, rating, '|');
            getline(ss, stock, '|');

            // trim helper
            auto trim = [](string &s) {
                while (!s.empty() && s[0] == ' ') s.erase(0, 1);
                while (!s.empty() && (s.back() == ' ' || s.back() == '\r' || s.back() == '\n'))
                    s.pop_back();
            };

            trim(id);
            trim(name);
            trim(price);
            trim(rating);
            trim(stock);

            Product p(
                stoi(id),
                name,
                stod(price),
                stod(rating),
                stoi(stock)
            );

            bst.insert(p);
        }

        file.close();
        cout << "Products loaded successfully.\n";
    }

};


#endif