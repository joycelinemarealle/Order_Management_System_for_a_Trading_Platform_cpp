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
        std::cout << "Order with id " << orderId << " was found" << std::endl;
        return &(it->second); //return address
    }
    return nullptr;
}

//Point to const Order.Can view but not change
std::vector<const Order *> OrderManager::getAllOrders() const {
    //Empty vector
    std::vector<const Order *> allOrders;

    //Loop over each element in orders map. loop as reference not actual object.Efficiency
    for (const auto &pair: orders) {
        //pair.first = orderId
        //pair.second = Order object

        allOrders.push_back(&(pair.second)); //first order at index 0 [1], [1,2]
    };
    return allOrders;
}

//Print order
void OrderManager::printOrders() const {
    for (const auto &pair: orders) {
        const auto &order = pair.second;
        std::cout << "\nOrder has ID:" << order.getId() << ", Price: " << order.getPrice()
                << ", Quantity:" << order.getQuantity() << ", Side: " <<
                (order.getSide() == OrderSide::Buy ? "Buy" : "Sell") << ", Status: ";
        switch (order.getStatus()) {
            case OrderStatus::New: std::cout << "New";
                break;
            case OrderStatus::PartiallyFilled: std::cout << "PartiallyFilled";
                break;
            case OrderStatus::Filled: std::cout << "Filled";
                break;
            case OrderStatus::Cancelled: std::cout << "Cancelled";
                break;
            default:
                std::cout << "Order" << order.getId() << "not found." << std::endl;
        }
    } //if not any of the status then
}
