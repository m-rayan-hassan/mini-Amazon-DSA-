#include "Admin.h"

#include <iostream>
using namespace std;

void Admin::login(ProductBST &pBST) {
    string inputId, inputPass;

    cout << "Enter Admin ID: ";
    cin >> inputId;
    cout << "Enter password: ";
    cin >> inputPass;

    ifstream file("data/admins.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open admins.txt\n";
        return;
    }

    string line;
    getline(file, line); // skip heading

    bool authenticated = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, pass;

        getline(ss, id, '|');
        getline(ss, pass, '|');

        // trim spaces
        auto trim = [](string &s){
            while (!s.empty() && (s[0] == ' ')) s.erase(0, 1);
            while (!s.empty() && (s.back() == ' ' || s.back() == '\r' || s.back() == '\n'))
                s.pop_back();
        };

        trim(id);
        trim(pass);

        if (id == inputId && pass == inputPass) {
            authenticated = true;
            break;
        }
    }

    file.close();

    if (authenticated) {
        cout << "Admin login successful!\n";
        adminOptions(pBST);
    }
    else {
        cout << "Invalid Admin ID or password.\n";
    }
}

void Admin::adminOptions(ProductBST &pBST) {
    int choice;
    while (true) {
        cout << "1. View all Products" << endl;
        cout << "2. Sort Products by Stock (Lowest to highest)" << endl;
        cout << "3. View all Orders" << endl;
        cout << "4. View To Dispatch Orders" << endl;
        cout << "5. Dispatch Orders" << endl;
        cout << "6. Update Product Stock" << endl;
        cout << "7. Update Product Price" << endl;
        cout << "8. Exit" << endl;
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                pBST.displayInorder();
                break;
        }
    }
}


