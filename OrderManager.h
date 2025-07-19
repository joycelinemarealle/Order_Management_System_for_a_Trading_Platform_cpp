//
// Created by Joyceline Marealle on 7/19/25.
//

#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H
#include "Order.h"
#include <unordered_map>
#include <vector>

class OrderManager
{
  private:
    int nextOrderId;
    std::unordered_map<int, Order> orders;

  public:
    int submitOrder(OrderSide side, double price, int quantity);
    bool cancelOrder(int orderId);
    const Order* getOrder(int orderId) const;
    std::vector<const Order*> getAllOrders() const;
 };
#endif //ORDERMANAGER_H
