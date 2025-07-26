#include "Order.h"

//consturctor

Order::Order(int id, double price, int quantity, OrderSide side, OrderStatus status)
    : id(id),price(price),quantity(quantity),side(side),status(status){}

//Getters
int Order::getId() const {return id;}
double Order::getPrice() const {return price;}
int Order::getQuantity() const {return quantity;}
OrderSide Order::getSide() const {return side;}
OrderStatus Order::getStatus() const {return status;}


//Fill part or all of the order
void Order::fill(int quantityFilled){
  filledQuantity += quantityFilled;
  if (filledQuantity >= quantity){
    status = OrderStatus::Filled;
    filledQuantity = quantity; //cap to max quantity
  } else {
    status = OrderStatus::PartiallyFilled;
   }
}

//check if order is fully filled
bool Order::isFilled() const {
    return filledQuantity >= quantity;
}
