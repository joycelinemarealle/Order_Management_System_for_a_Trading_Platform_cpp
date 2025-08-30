#ifndef ORDER_H
#define ORDER_H
#include <string>

enum class OrderSide { Buy, Sell };

enum class OrderStatus { New, PartiallyFilled, Filled, Cancelled };

class Order {
private:
    int id;
    double price;
    int quantity;
    OrderSide side;
    OrderStatus status;
    int filledQuantity = 0; //track how many units filled

public:
    Order(int id, double price, int quantity, OrderSide side, OrderStatus status);

    int getId() const;

    double getPrice() const;

    int getQuantity() const;

    OrderSide getSide() const;

    OrderStatus getStatus() const;

    int getFilledQuantity() const;

    void setStatus(OrderStatus newStatus);

    void setFilledQuantity(int filled);

    void fill(int quantityFilled);

    bool isFilled() const;
};

#endif //ORDER_H
