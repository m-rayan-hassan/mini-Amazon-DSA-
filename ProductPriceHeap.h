#ifndef PROJECT_PRODUCTPRICEHEAP_H
#define PROJECT_PRODUCTPRICEHEAP_H

#include <iostream>

#include "Product.h"
using namespace std;

class ProductPriceHeap {
    Product arr[100];
    int size;

public:
    ProductPriceHeap() {
        size = 0;
    }

    void insert(Product p) {
        int index = size;
        arr[index] = p;
        size++;

        while (index != 0 && arr[(index - 1)/2].price < arr[index].price) {
            swap(arr[index], arr[(index - 1)/2]);
            index = (index - 1) / 2;
        }
    }

    void heapifyDown(int i) {
        int largest = i;
        int left = 2*i + 1;
        int right = 2*i + 2;

        if (left < size && arr[left].price > arr[largest].price)
            largest = left;

        if (right < size && arr[right].price > arr[largest].price)
            largest = right;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapifyDown(largest);
        }
    }

    void display() {
        cout << "\n----------- Sorted Products By Price (Low -> High) -----------\n";
        for (int i = 0; i < size; i++) {
            cout << "Product ID: " << arr[i].productId << endl;
            cout << "Product Name: " << arr[i].productName << endl;
            cout << "Price: " << arr[i].price << endl;
            cout << "Rating: " << arr[i].rating << endl;
            cout << "Items Left: " << arr[i].stock << endl;
            cout << "\n";
            cout << endl;
        }
    }

    void heapSort() {
        int arrSize = size;
        while (size >= 1) {
            swap(arr[0], arr[size - 1]);
            size--;
            heapifyDown(0);
        }
        size = arrSize;
    }
};


#endif //PROJECT_PRODUCTPRICEHEAP_H