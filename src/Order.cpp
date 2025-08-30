#include "../include/Order.h"

//constructor valids price and quantity
Order::Order(int id, double price, int quantity, OrderSide side, OrderStatus status)
    : id(id), price(price), quantity(quantity), side(side), status(status) {
    if (price < 0) {
        throw std::invalid_argument("Price must be non-negative");
    }
    if (quantity <0) {
        throw std::invalid_argument("Quantity must be non-negative");
    }
}

//Getters
int Order::getId() const { return id; }
double Order::getPrice() const { return price; }
int Order::getQuantity() const { return quantity; }
OrderSide Order::getSide() const { return side; }
OrderStatus Order::getStatus() const { return status; }

void Order::setStatus(OrderStatus newStatus) {
    status = newStatus;
}
//manual / restore filled quantity state
void Order::setFilledQuantity(int filled) {
    if (filled <0) {
        throw std::invalid_argument("Invalid filled quantity");
    }
    if (filled >= 0 && filled <= quantity) {
        filledQuantity = filled;

        //updated status
        if (filledQuantity == quantity) {
            status = OrderStatus::Filled;
        } else if (filledQuantity > 0) {
            status = OrderStatus::PartiallyFilled;
        } else {
            status = OrderStatus::New; //filled quantity zero the new + covers if filled <0
        }
    }
}

//Fill part or all of the order
void Order::fill(int quantityFilled) {
    if (quantityFilled <0) {
        throw std::invalid_argument("Cannot fill negative quantity");
    }
    if (quantityFilled ==0) return; //keep status

    filledQuantity += quantityFilled;
    if (filledQuantity >= quantity) {
        status = OrderStatus::Filled;
        filledQuantity = quantity; //cap to max quantity

    } else {
        status = OrderStatus::PartiallyFilled;
    }
}

//get filled quantity
int Order::getFilledQuantity() const{
 return filledQuantity;
};

//check if order is fully filled
bool Order::isFilled() const {
    return filledQuantity >= quantity;
}
