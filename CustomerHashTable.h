#ifndef PROJECT_HASHTABLE_H
#define PROJECT_HASHTABLE_H

#include <iostream>
#include <list>
#include <string>
using namespace std;

class Customer;

class CustomerHashTable {
private:
    static const int TABLE_SIZE = 101;
    list<Customer*> table[TABLE_SIZE];

    int hashFunction(const string &key) {
        int hash = 0;
        for (char ch : key) hash += ch;
        return hash % TABLE_SIZE;
    }

public:
    void insert(Customer *c) {
        int index = hashFunction(c->getUsername());
        table[index].push_back(c);
    }

    Customer* search(const string &username) {
        int index = hashFunction(username);
        for (auto &c : table[index]) {
            if (c->getUsername() == username) return c;
        }
        return nullptr;
    }
};

#endif
