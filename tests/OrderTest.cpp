//
// Created by Joyceline Marealle on 8/18/25.
//
#include <gtest/gtest.h>
#include "../include/Order.h"

//Happy
TEST(OrderTest, ConstructorInitializesCorrectly) {
    Order order (1,100.00,10,OrderSide::Buy, OrderStatus::New);
    EXPECT_EQ(order.getId(),1);
    EXPECT_EQ(order.getPrice(), 100.00);
    EXPECT_EQ(order.getQuantity(),10);
    EXPECT_EQ(order.getSide(), OrderSide::Buy);
    EXPECT_EQ(order.getStatus(),OrderStatus::New );
}
TEST(OrderTest, FillUpdatesFilledQuantityAndStatus) {
    Order order (1,100.00,10,OrderSide::Buy, OrderStatus::New);
    order.fill(4);
    EXPECT_EQ(order.getFilledQuantity(), 4);
    EXPECT_EQ(order.getStatus(), OrderStatus::PartiallyFilled);
    EXPECT_FALSE(order.isFilled());
}
//Boundary,erronous, happy path if order has -ve, is filling quantity > quantity of order, fillquantity -ve
//Boundary min and max
TEST(OrderTest, OrderFillDoesNotExceedQuantity) {
    Order order (1,100.00,10,OrderSide::Buy, OrderStatus::New);
    order.fill(3);
    EXPECT_EQ(order.getFilledQuantity(), 3);
    order.fill(8); //cannot go above 10

    EXPECT_EQ(order.getFilledQuantity(), 10);
    EXPECT_TRUE(order.isFilled());
    EXPECT_EQ(order.getStatus(), OrderStatus::Filled);
}

TEST(OrderTest, OrderFillZeroHasStatusNew) {
    Order order (1,100.00,10,OrderSide::Buy, OrderStatus::New);
    order.fill(0);
    EXPECT_EQ(order.getStatus(), OrderStatus::New);
    EXPECT_EQ(order.getFilledQuantity(), 0);
    EXPECT_FALSE(order.isFilled());
}


//Erroneous
TEST(OrderTest, NegativeFillThrowsError) {
    Order order (1,100.00,10,OrderSide::Buy, OrderStatus::New);
    EXPECT_THROW(order.fill(-2), std::invalid_argument);
}

TEST(OrderTest, NegativeSetFilledQuantityThrowsError) {
    Order order (1,100.00,10,OrderSide::Buy, OrderStatus::New);
    EXPECT_THROW(order.setFilledQuantity(-10), std::invalid_argument);
}

//Negative price/quantity should not create order
TEST(OrderTest, ConstructorThrowsNegativePrice) {
    EXPECT_THROW(Order order (1,-100.00,-10,OrderSide::Buy, OrderStatus::New),
        std::invalid_argument);
}
TEST(OrderTest, ConstructoThrowsNegativeQuantity) {
    EXPECT_THROW(Order order (1,100.00,-10,OrderSide::Buy, OrderStatus::New),
        std::invalid_argument);
}