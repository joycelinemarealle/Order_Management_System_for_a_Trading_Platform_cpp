//
// Created by Joyceline Marealle on 7/19/25.
//

#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H
#include "Order.h"
#include <iostream> //std::cout
#include <unordered_map>
#include <vector>

class OrderManager {
private:
    int nextOrderId = 1; //start IDs at 1
    std::unordered_map<int, Order> orders;

public:
    int submitOrder(OrderSide side, double price, int quantity, OrderStatus status);

    bool cancelOrder(int orderId);

    const Order *getOrder(int orderId) const;

    std::vector<const Order *> getAllOrders() const;

    void printOrders() const;
};
#endif //ORDERMANAGER_H
