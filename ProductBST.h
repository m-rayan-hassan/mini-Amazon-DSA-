#ifndef PROJECT_PRODUCTBST_H
#define PROJECT_PRODUCTBST_H

#include <iostream>
#include "Product.h"
#include <fstream>
#include "FileHandler.h"
using namespace std;


struct Node {
    Product data;
    Node* left;
    Node* right;
    Node(Product &val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class ProductBST {
    private:
    Node* root;

    Node* insert(Node* node, Product &val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val.productId < node->data.productId) {
            node->left = insert(node->left, val);
        } else if (val.productId > node->data.productId) {
            node->right = insert(node->right, val);
        }

        return node;
    }

    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << "Product ID: " << node->data.productId << endl;
        cout << "Product Name: " << node->data.productName << endl;
        cout << "Price: " << node->data.price << endl;
        cout << "Rating: " << node->data.rating << endl;
        cout << "Items Left: " << node->data.stock << endl;
        cout << "\n";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (node == nullptr) return;
        cout << "Product ID: " << node->data.productId << endl;
        cout << "Product Name: " << node->data.productName << endl;
        cout << "Price: " << node->data.price << endl;
        cout << "Rating: " << node->data.rating << endl;
        cout << "Items Left: " << node->data.stock << endl;
        cout << "\n";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        cout << "Product ID: " << node->data.productId << endl;
        cout << "Product Name: " << node->data.productName << endl;
        cout << "Price: " << node->data.price << endl;
        cout << "Rating: " << node->data.rating << endl;
        cout << "Items Left: " << node->data.stock << endl;
        cout << "\n";
    }

    Node* search(Node* node, int key) {
        if (node == nullptr || node->data.productId == key)
            return node;

        if (key < node->data.productId)
            return search(node->left, key);

        return search(node->right, key);
    }


    void updateQuantity(Node* node, int key, int qty, string type) {
        if (node == nullptr) return;

        if (key == node->data.productId) {
            if (type == "add")
                node->data.stock -= qty;
            else if (type == "undo")
                node->data.stock += qty;
            else if (type == "update")
                node->data.stock = qty;

            updateProductInFile(key, qty, type);
            return;
        }

        if (key < node->data.productId)
            updateQuantity(node->left, key, qty, type);
        else
            updateQuantity(node->right, key, qty, type);
    }

public:
    ProductBST() {
        root = nullptr;
    }

    void insert(Product &val) {
        root = insert(root, val);
    }

    void displayInorder() {
        inorder(root);
        cout << endl;
    }

    void displayPreorder() {
        preorder(root);
        cout << endl;
    }

    void displayPostorder() {
        postorder(root);
        cout << endl;
    }

    Node* search(int key) {
        if (search(root, key) == nullptr) {
            return nullptr;
        }
        return search(root, key);
    }

    void searchAndUpdateQuantity(int productId, int quantity, string type) {
        updateQuantity(root, productId, quantity, type);
    }


};
#endif //PROJECT_PRODUCTBST_H