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

TEST(OrderManagerTest, SubmitOrderThrowsErrorWithNegativePrice) {
OrderManager manager;
    EXPECT_THROW(
        manager.submitOrder(OrderSide::Buy, -100.0, 10, OrderStatus::New), std::invalid_argument);
}

TEST(OrderManagerTest, SubmitOrderThrowsErrorWithNegativeQuantity) {
OrderManager manager;
    EXPECT_THROW(manager.submitOrder(OrderSide::Sell, 100.0, -10, OrderStatus::New), std::invalid_argument);
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


TEST(OrderManagerTest, CancelOrderReturnsErrowWithInvalidOrderId) {
OrderManager manager;
    EXPECT_THROW(manager.cancelOrder(-1), std::invalid_argument);
}

TEST(OrderManagerTest, CancelOrderReturnsErrowWithNonExistingOrderId) {
    OrderManager manager;
    EXPECT_THROW(manager.cancelOrder(1000), std::invalid_argument);
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

TEST(OrderManagerTest,MatchOrderNoMatchDueToPrice) {
    OrderManager manager;
    const int buyOrderId = manager.submitOrder(OrderSide::Buy,105.2,10,OrderStatus::New);
    const int sellOrderId= manager.submitOrder(OrderSide::Sell, 200.32, 5, OrderStatus::New);
    const Order* buyOrder = manager.getOrder(buyOrderId);
    const Order* sellOrder = manager.getOrder(sellOrderId);
    manager.matchOrders();

    //not filled because bp<sp
    EXPECT_EQ(buyOrder->getStatus(), OrderStatus::New);
    EXPECT_EQ(sellOrder->getStatus(), OrderStatus::New);



}

TEST(OrderManagerTest, MatchSkipsCancelledOrders) {
    OrderManager manager;
    int sellId = manager.submitOrder(OrderSide::Sell, 100.0, 5, OrderStatus::New);
    int buyId = manager.submitOrder(OrderSide::Buy, 105.0, 5, OrderStatus::New);
    manager.cancelOrder(sellId); // cancel the sell

    manager.matchOrders();

    const Order* sell = manager.getOrder(sellId);
    const Order* buy = manager.getOrder(buyId);

    EXPECT_EQ(sell->getStatus(), OrderStatus::Cancelled);
    EXPECT_EQ(buy->getStatus(), OrderStatus::New); // should remain unchanged
}

TEST(OrderManagerTest, MatchOrderPartialFillAcrossMultipleSells) {
    OrderManager manager;
    int sell1 = manager.submitOrder(OrderSide::Sell, 100.0, 3, OrderStatus::New);
    int sell2 = manager.submitOrder(OrderSide::Sell, 101.0, 2, OrderStatus::New); // higher price, still matchable
    int buy = manager.submitOrder(OrderSide::Buy, 100.0, 4, OrderStatus::New);

    manager.matchOrders();

    const Order* buyOrder = manager.getOrder(buy);
    const Order* s1 = manager.getOrder(sell1);
    const Order* s2 = manager.getOrder(sell2);

    EXPECT_EQ(buyOrder->getStatus(), OrderStatus::Filled);
    EXPECT_EQ(buyOrder->getFilledQuantity(), 4);
    EXPECT_EQ(s1->getFilledQuantity(), 3);
    EXPECT_EQ(s2->getFilledQuantity(), 1); // only partially fills s2
}
TEST(OrderManagerTest, MatchMultipleSellOrdersAgainstOneBuy) {
    OrderManager manager;
    int sell1 = manager.submitOrder(OrderSide::Sell, 100.0, 3, OrderStatus::New);
    int sell2 = manager.submitOrder(OrderSide::Sell, 99.0, 2, OrderStatus::New);
    int buy = manager.submitOrder(OrderSide::Buy, 105.0, 5, OrderStatus::New);

    manager.matchOrders();

    const Order* buyOrder = manager.getOrder(buy);
    const Order* s1 = manager.getOrder(sell1);
    const Order* s2 = manager.getOrder(sell2);

    EXPECT_EQ(buyOrder->getStatus(), OrderStatus::Filled);
    EXPECT_EQ(buyOrder->getFilledQuantity(), 5);
    EXPECT_EQ(s1->getStatus(), OrderStatus::Filled);
    EXPECT_EQ(s2->getStatus(), OrderStatus::Filled);
}

TEST(OrderManagerTest, SubmitOrderIncrementsOrderId) {
    OrderManager manager;
    int id1 = manager.submitOrder(OrderSide::Buy, 100.0, 10, OrderStatus::New);
    int id2 = manager.submitOrder(OrderSide::Buy, 200.0, 5, OrderStatus::New);
    EXPECT_EQ(id2, id1 + 1);
}

