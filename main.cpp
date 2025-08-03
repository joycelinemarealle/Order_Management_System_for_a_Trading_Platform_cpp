#include <iostream>
#include "OrderManager.h"


int main() {
    OrderManager manager;

    //submit orders
    int id1 = manager.submitOrder(OrderSide::Buy, 100.5, 10, OrderStatus::New);
    int id2 = manager.submitOrder(OrderSide::Sell, 101.0, 5, OrderStatus::New);


   //cancel order 2
    bool cancelOrderid2 = manager.cancelOrder(id2);

    return id1;

}
