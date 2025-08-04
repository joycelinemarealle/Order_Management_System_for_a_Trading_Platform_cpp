//
// Created by Joyceline Marealle on 7/26/25.
//
#include "OrderManager.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>

//Add a new order and return its unique id
int OrderManager::submitOrder(OrderSide side, double price, int quantity, OrderStatus status) {
    //geneate unique id, sequantial simple to manage vs random generator
    int orderId = nextOrderId++;

    //create new order. status new auto for new orders
    Order newOrder(orderId, price, quantity, side, OrderStatus::New);

    //store this new order object
    orders.insert(std::make_pair(orderId, newOrder));

    //Notify and return
    std::cout << "Order submitted:ID" << orderId << std::endl;
    return orderId;
}

bool OrderManager::cancelOrder(int orderId) {
    auto it = orders.find(orderId); //find order by id
    if (it != orders.end()) {
        //if found
        it->second.setStatus(OrderStatus::Cancelled); //set to cancelled
        std::cout << "Order " << orderId << " cancelled." << std::endl;
    }
    return true; //successs
}


const Order *OrderManager::getOrder(int orderId) const {
    //find order by id
    auto it = orders.find(orderId);
    if (it != orders.end()) {
        std::cout << "Order with id " << orderId << " was found"<<std::endl;
        return &(it->second) ; //return address
    }
    return nullptr;
}

//std::vector<const Order*> OrderManager::getAllOrders() const {
//    return std::vector< const Order*>;
//}
