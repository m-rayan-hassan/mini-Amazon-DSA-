#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

void updateProductInFile(int productId, int quantity, string type) {
    ifstream inFile("data/products.txt");
    if (!inFile.is_open()) {
        cout << "Error opening products file\n";
        return;
    }

    vector<string> lines;
    string line;

    // Keep header
    getline(inFile, line);
    lines.push_back(line);

    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, name, price, rating, stock;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, price, '|');
        getline(ss, rating, '|');
        getline(ss, stock);

        int pid = stoi(id);
        int currentStock = stoi(stock);

        if (pid == productId) {
            if (type == "add")
                currentStock -= quantity;
            else if (type == "undo")
                currentStock += quantity;
        }

        lines.push_back(
            id + " | " + name + " | " + price + " | " + rating + " | " + to_string(currentStock)
        );
    }

    inFile.close();

    ofstream outFile("data/products.txt", ios::trunc);
    for (auto &l : lines)
        outFile << l << endl;
    outFile.close();
}
