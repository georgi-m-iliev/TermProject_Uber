#include <iostream>
#include <cstring>
#include <sstream>
#include "Uber.h"

const int BUFFER_SIZE = 1024;

int main() {
    Uber service;
    char buffer[BUFFER_SIZE];
    while(true) {
        std::cout << "> ";
        std::cin.getline(buffer, BUFFER_SIZE);

        if(strcmp(buffer, "exit") == 0) {
            std::cout << "Exiting..." << std::endl;
            break;
        }

        std::stringstream ss(buffer);
        ss.getline(buffer, BUFFER_SIZE, ' ');

        if(strcmp(buffer, "register") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            if(strcmp(buffer, "client") == 0) {
                try {
                    service.registerUser(UserType::Client, ss);
                }
                catch(const std::exception& ex) {
                    std::cout << ex.what() << std::endl;
                }
            }
            else if(strcmp(buffer, "driver") == 0) {
                try {
                    service.registerUser(UserType::Driver, ss);
                }
                catch(const std::exception& ex) {
                    std::cout << ex.what() << std::endl;
                }
            }
            else {
                std::cout << "Unknown user type! Try again!" << std::endl;
            }
        }
        else if(strcmp(buffer, "login") == 0) {
            try {
                service.loginUser(ss);
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "logout") == 0) {
            try {
                service.logoutUser();
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "change_password") == 0) {
            ss.getline(buffer, BUFFER_SIZE);
            try {
                service.changePassword(buffer);
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "whoami") == 0) {
            try {
                service.whoami();
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "list_orders") == 0) {
            try {
                service.listOrders();
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "order") == 0) {
            try {
                service.order();
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "check_order") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            try {
                service.checkOrder(buffer);
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "cancel_order") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            try {
                service.cancelOrder(buffer);
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "pay") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            double value;
            ss >> value;
            try {
                service.payOrder(buffer, value);
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "rate") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            short value = 0;
            ss >> value;
            try {
                service.rateOrder(buffer, value);
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "add_money") == 0) {
            double value = 0;
            ss >> value;
            try {
                service.addMoney(value);
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "print") == 0) {
            try {
                service.print();
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "change_address") == 0) {
            try {
                service.changeAddress(ss);
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "check_messages") == 0) {
            try {
                service.checkMessages();
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "accept_order") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            short minutes = 0;
            ss >> minutes;
            double amount = 0;
            ss >> amount;
            ss.ignore(1);
            try {
                service.acceptOrder(buffer, minutes, amount);
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "decline_order") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            try {
                service.declineOrder(buffer);
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "pickup_passengers") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            try {
                service.pickupPassenger(buffer);
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "finish_order") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            try {
                service.finishOrder(buffer);
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "accept_payment") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            double amount = 0;
            ss >> amount;
            ss.ignore(1);
            try {
                service.acceptPayment(buffer, amount);
            }
            catch(const std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else {
            std::cout << "Unknown command!" << std::endl;
            continue;
        }
        std::cout << std::endl;
    }
}