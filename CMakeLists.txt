cmake_minimum_required(VERSION 4.0)
project(project)

set(CMAKE_CXX_STANDARD 20)

add_executable(project main.cpp
        Customer.h
        Admin.h
        CustomerHashTable.h
        DataLoader.h
        Customer.cpp
        Product.h
        ProductBST.h
        Admin.cpp
        CartItem.h
        CartStack.h
        Cart.cpp
        Cart.h
        DispatchQueue.h
        Order.h
        ProductPriceHeap.h
        FileHandler.cpp
        FileHandler.h
)
