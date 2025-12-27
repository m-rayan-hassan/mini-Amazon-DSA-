#include "Admin.h"
#include "DispatchQueue.h"
#include "Order.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

static const string ORDERS_FILE = "data/orders.txt";

// -------- Helper: trim function ----------
static void trim(string &s) {
    while (!s.empty() && (s.front() == ' ')) s.erase(0, 1);
    while (!s.empty() &&
           (s.back() == ' ' || s.back() == '\r' || s.back() == '\n'))
        s.pop_back();
}

// ----------- View All Orders ----------------
void Admin::viewAllOrders() {
    ifstream file("data/orders.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open orders.txt\n";
        return;
    }

    cout << "\n====== ALL ORDERS ======\n";

    string line;
    getline(file, line); // skip heading

    while (getline(file, line)) {
        stringstream ss(line);
        string oid, user, pid, pname, qty, status;

        getline(ss, oid, '|');
        getline(ss, user, '|');
        getline(ss, pid, '|');
        getline(ss, pname, '|');
        getline(ss, qty, '|');
        getline(ss, status, '|');

        auto trim = [](string &s) {
            while (!s.empty() && s[0] == ' ') s.erase(0, 1);
            while (!s.empty() && (s.back()==' ' || s.back()=='\n' || s.back()=='\r')) s.pop_back();
        };

        trim(oid); trim(user); trim(pid); trim(pname); trim(qty); trim(status);

        cout << "OrderID: " << oid
             << " | User: " << user
             << " | Product: " << pname
             << " | Qty: " << qty
             << " | Status: " << status << endl;
    }

    file.close();
}


void loadDispatchOrders(DispatchQueue &q) {
    if (!q.isEmpty()) return;  // Only load if queue is empty

    ifstream file("data/orders.txt");
    if (!file.is_open()) {
        cout << "Error: Could not open orders.txt\n";
        return;
    }

    string line;
    getline(file, line);  // skip header

    Order currentOrder;
    bool hasOrder = false;
    int lastOrderId = -1;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string oidStr, username, pidStr, pname, qtyStr, status;

        getline(ss, oidStr, '|');
        getline(ss, username, '|');
        getline(ss, pidStr, '|');
        getline(ss, pname, '|');
        getline(ss, qtyStr, '|');
        getline(ss, status, '|');

        // Trim spaces
        auto trim = [](string &s) {
            while (!s.empty() && isspace(s.front())) s.erase(s.begin());
            while (!s.empty() && isspace(s.back())) s.pop_back();
        };
        trim(oidStr); trim(username); trim(pidStr);
        trim(pname); trim(qtyStr); trim(status);

        if (status != "To Dispatch") continue;

        int oid = stoi(oidStr);
        int pid = stoi(pidStr);
        int qty = stoi(qtyStr);

        if (oid != lastOrderId) {
            if (hasOrder) {
                q.enqueue(currentOrder);
            }

            currentOrder = Order();
            currentOrder.orderId = oid;
            currentOrder.customerUsername = username;
            currentOrder.status = "To Dispatch";
            currentOrder.items = CartStack();

            hasOrder = true;
        }

        currentOrder.items.push(CartItem(pid, pname, qty));
        lastOrderId = oid;
    }

    if (hasOrder) q.enqueue(currentOrder);

    file.close();
    cout << "Loaded To Dispatch Orders into Dispatch Queue.\n";
}



// ---------- Update Orders.txt After Dispatch ----------
void updateOrderStatusInFile(int orderId) {
    ifstream in(ORDERS_FILE);
    vector<string> lines;
    string line;

    getline(in, line);                          // keep header
    string header = line;
    lines.push_back(header);

    while (getline(in, line)) {
        if (line.find(to_string(orderId) + " |") == 0) {
            // change status to Delivered
            size_t pos = line.rfind('|');
            line = line.substr(0, pos) + "| Delivered";
        }
        lines.push_back(line);
    }
    in.close();

    ofstream out(ORDERS_FILE, ios::trunc);
    for (string &l : lines) out << l << endl;
    out.close();
}



// ------------ Admin Login ------------------------
void Admin::login(ProductBST &pBST, DispatchQueue &q) {
    string inputId, inputPass;
    cout << "\n----------- ADMIN LOGIN -----------\n";

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
    getline(file, line); // skip header

    bool authenticated = false;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, pass;

        getline(ss, id, '|');
        getline(ss, pass, '|');

        trim(id);
        trim(pass);

        if (id == inputId && pass == inputPass) {
            authenticated = true;
            break;
        }
    }

    file.close();

    if (authenticated) {
        cout << "\nAdmin login successful!\n";
        adminOptions(pBST, q);
    } else {
        cout << "\nInvalid Admin ID or Password!\n";
    }
}



// ------------ Admin Options Menu -------------------
void Admin::adminOptions(ProductBST &pBST, DispatchQueue &q) {
    char choice;
    q.clear();
    loadDispatchOrders(q);

    while (true) {
        cout << "\n=========== ADMIN PANEL ===========\n";
        cout << "1. View All Products\n";
        cout << "2. Sort Products by Stock\n";
        cout << "3. View All Orders\n";
        cout << "4. View To-Dispatch Orders\n";
        cout << "5. Dispatch Next Order\n";
        cout << "6. Update Product Stock\n";
        cout << "7. Update Product Price\n";
        cout << "8. Logout\n";
        cout << "==================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                pBST.displayInorder();
                break;

            case '2':
                cout << "(Sorting not implemented yet)\n";
                break;

            case '3':
                viewAllOrders();
                break;

            case '4':
                q.display();
                break;

            case '5':
                if (q.isEmpty()) {
                    cout << "No orders to dispatch!\n";
                } else {
                    Order delivered = q.dequeue();
                    cout << "\nDispatched Order:\n";
                    cout << "Order Id: " << delivered.orderId << endl;
                    cout << "Customer Username: " << delivered.customerUsername << endl;
                    cout << "Items: " << endl;
                    delivered.items.display();
                    updateOrderStatusInFile(delivered.orderId);
                }
                break;

            case '6':
                cout << "(Stock update code here)\n";
                break;

            case '7':
                cout << "(Price update code here)\n";
                break;

            case '8':
                cout << "\nExiting Admin Panel...\n";
                return;

            default:
                cout << "Invalid choice!\n";
        }
    }
}
