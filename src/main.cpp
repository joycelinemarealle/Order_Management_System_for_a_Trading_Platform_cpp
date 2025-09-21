#include <iostream>
#include "OrderManager.h"
#include <string>

void printMenu() {
    std::cout << "\nWelcome to JLM Trading System. What would you like to do today? Select a number " << std::endl;
    std::cout << "\n1 Add new order\n";
    std::cout << "\n2 Cancel an Existing order\n";
    std::cout << "\n3 Fill an order\n";
    std::cout << "\n4 View all orders\n";
    std::cout << "\n5 Match orders\n";
    std::cout << "\n6 Exit program";
}

int main() {
    OrderManager manager;
    bool running = true;

    while (running) {
        printMenu();

        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: {
                int quantity, sideInput;
                double price;
                std::cout << "Enter side (0=Buy,1=Sell)";
                std::cin >> sideInput;
                std::cout << "Enter quantity";
                std::cin >> quantity;
                std::cout << "Enter price";
                std::cin >> price;
                OrderSide side = (sideInput == 0) ? OrderSide::Buy : OrderSide::Sell;
                manager.submitOrder(side, price, quantity, OrderStatus::New);
                break;
            }
            case 2: {
                int idInput;
                std::cout << "Enter order Id to cancel:";
                std::cin >> idInput;
                manager.cancelOrder(idInput);
                break;
            }
            case 3: manager.printOrders();
                break;
            case 4: manager.matchOrders();
                break;
            case 5: ;
                break;
            case 6: ;
                break;
            default: std::cout << "Select correct option";
                break;
        }
    }

}
