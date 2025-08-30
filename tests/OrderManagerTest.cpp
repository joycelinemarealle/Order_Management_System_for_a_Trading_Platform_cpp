//
// Created by Joyceline Marealle on 8/18/25.
//
#include <gtest/gtest.h>
#include "../include/OrderManager.h"

TEST(OrderManagerTest, SubmitOrderCreatesNewBuyOrder) {
    OrderManager manager;
    int orderId = manager.submitOrder(OrderSide::Sell, 100.00, 10, OrderStatus::New);
    const Order* order = manager.getOrder(orderId); //* sticks with type not variable name

    ASSERT_NE(order,nullptr); //assert that order is not null ptr
    EXPECT_EQ(order->getId(), orderId);
    EXPECT_EQ(order->getPrice(), 100.00);
    EXPECT_EQ(order->getQuantity(), 10);
    EXPECT_EQ(order->getSide(), OrderSide::Sell);
    EXPECT_EQ(order->getStatus(), OrderStatus::New);
}

TEST(OrderManagerTest, CancelOrderUpdatesStatus) {
    OrderManager manager;
    int orderId = manager.submitOrder(OrderSide::Sell, 100.00, 10, OrderStatus::New);
    const Order* order = manager.getOrder(orderId); //* sticks with type not variable name
    bool result = manager.cancelOrder(orderId);
    EXPECT_TRUE(result);
    ASSERT_NE(order,nullptr);
    EXPECT_EQ(order->getStatus(), OrderStatus::Cancelled);

}

TEST(OrderManagerTest, GetOrderReturnsCorrectOrder) {
    OrderManager manager;
    const int orderId = manager.submitOrder(OrderSide::Buy, 100.0, 5, OrderStatus::New);
    const Order* order = manager.getOrder(orderId); //* sticks with type not variable name
    EXPECT_NE(order, nullptr);
    EXPECT_EQ(order->getId(),orderId);
}
TEST(OrderManagerTest, GetOrderReturnsNullForInvalidId) {
    OrderManager manager;
    const Order* order = manager.getOrder(999);
    EXPECT_EQ(order, nullptr);
}
TEST(OrderManagerTest, GetAllOrdersReturnsSllSubmittedOrders ) {
    OrderManager manager;
    manager.submitOrder(OrderSide::Buy, 100.0, 5, OrderStatus::New);
    manager.submitOrder(OrderSide::Sell, 105.0, 3, OrderStatus::New);
    auto orders= manager.getAllOrders();
    EXPECT_EQ (orders.size(),2); //the array will have 2 orders
}


TEST(OrderManagerTest, MatchOrderForPartialFillSellSide) {
OrderManager manager;
    const int buyOrderId = manager.submitOrder(OrderSide::Buy, 105.00, 11, OrderStatus::New);
    const int sellOrderId =  manager.submitOrder(OrderSide::Sell, 100.0, 5, OrderStatus::New);
    const Order* buyOrder= manager.getOrder(buyOrderId);
    const Order* sellOrder = manager.getOrder(sellOrderId);
    manager.matchOrders();

    //check if sellOrder full filled
    EXPECT_EQ(sellOrder->getStatus(), OrderStatus::Filled);
    EXPECT_EQ(sellOrder->getFilledQuantity(), 5);
    EXPECT_EQ(buyOrder->getStatus(), OrderStatus::PartiallyFilled);
    EXPECT_EQ(buyOrder->getFilledQuantity(), 5);
}

TEST(OrderManagerTest, MatchOrderForFullyFilledSellandBuySides) {
    OrderManager manager;
    const int buyOrderId = manager.submitOrder(OrderSide::Buy, 105.00, 5, OrderStatus::New);
    const int sellOrderId =  manager.submitOrder(OrderSide::Sell, 100.0, 5, OrderStatus::New);
    const Order* buyOrder= manager.getOrder(buyOrderId);
    const Order* sellOrder = manager.getOrder(sellOrderId);
    manager.matchOrders();

    //check if sellOrder full filled
    EXPECT_EQ(sellOrder->getStatus(), OrderStatus::Filled);
    EXPECT_EQ(sellOrder->getFilledQuantity(), 5);
    EXPECT_EQ(buyOrder->getStatus(), OrderStatus::Filled);
    EXPECT_EQ(buyOrder->getFilledQuantity(), 5);
}
