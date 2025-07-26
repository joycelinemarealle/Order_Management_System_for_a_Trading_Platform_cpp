//
// Created by Joyceline Marealle on 7/26/25.
//
//
// Created by Joyceline Marealle on 7/26/25.
//
#include "OrderManager.h"
#include <iostream>

//Add a new order and return its nique id
int OrderManager::submitOrder(OrderSide side, double price, int quantity, OrderStatus status){
    //geneate unique id, sequantial simple to manage vs random generator
    int orderId = nextOrderId++;

    //create new order. status new auto for new orders
    Order newOrder(orderId,price,quantity, side,OrderStatus::New);

    //store this  new order object
    orders.insert(std::make_pair(orderId,newOrder));

    //Notify and return
    std::cout <<"Order submitted:ID" << orderId << std::endl;
    return orderId;
}

bool OrderManager::cancelOrder(int orderId){
    return true;}


const Order* OrderManager::getOrder(int orderId) const {
    return nullptr;
}

std::vector<const Order*> OrderManager::getAllOrders() const {
    return std::vector< const Order*>;
}
