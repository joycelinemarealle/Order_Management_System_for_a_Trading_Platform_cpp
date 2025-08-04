#include <iostream>
#include "OrderManager.h"


int main() {
    OrderManager manager;

    //submit orders
    int id1 = manager.submitOrder(OrderSide::Buy, 100.5, 10, OrderStatus::New);
    int id2 = manager.submitOrder(OrderSide::Sell, 101.0, 5, OrderStatus::New);


    //cancel order 2
    bool cancelOrderid2 = manager.cancelOrder(id2);


    //Get order 1
    auto order = manager.getOrder(id1);
    //if present print out
    if (order != nullptr) {
        std::cout << "Order has ID:" << order->getId() << ", Price: " << order->getPrice()
                << ", Quantity:" << order->getQuantity() << ", Side: " <<
                (order->getSide() == OrderSide::Buy ? "Buy" : "Sell") << ", Status: ";
        switch (order->getStatus()) {
            case OrderStatus::New: std::cout << "New";
                break;
            case OrderStatus::PartiallyFilled: std::cout << "PartiallyFilled";
                break;
            case OrderStatus::Filled: std::cout << "Filled";
                break;
            case OrderStatus::Cancelled: std::cout << "Cancelled";
                break;
        }
    } //if not any of the status then
    else {
        std::cout << "Order" << id1 << "not found." << std::endl;
    }

    return 0;
}
