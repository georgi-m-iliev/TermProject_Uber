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
                catch(std::exception& ex) {
                    std::cout << ex.what() << std::endl;
                }
            }
            else if(strcmp(buffer, "driver") == 0) {
                try {
                    service.registerUser(UserType::Driver, ss);
                }
                catch(std::exception& ex) {
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
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "logout") == 0) {
            try {
                service.logoutUser();
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "change_password") == 0) {
            ss.getline(buffer, BUFFER_SIZE);
            try {
                service.changePassword(buffer);
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "whoami") == 0) {
            try {
                service.whoami();
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "order") == 0) {
            try {
                service.order();
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "check_order") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            try {
                service.checkOrder(buffer);
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "cancel_order") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            try {
                service.cancelOrder(buffer);
            }
            catch(std::exception& ex) {
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
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "rate") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            short value;
            ss >> value;
            try {
                service.rateOrder(buffer, value);
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "add_money") == 0) {
            double value;
            ss >> value;
            try {
                service.addMoney(value);
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "print") == 0) {
            try {
                service.print();
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "change_address") == 0) {
            try {
                service.changeAddress();
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "check_messages") == 0) {
            try {
                service.checkMessages();
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "print") == 0) {
            try {
                service.print();
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "accept_order") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            short minutes;
            ss >> minutes;
            double amount;
            ss >> amount;
            ss.ignore(1);
            try {
                service.acceptOrder(buffer, minutes, amount);
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "decline_order") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            try {
                service.declineOrder(buffer);
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "pickup_passengers") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            try {
                service.pickupPassenger(buffer);
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "finish_order") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            try {
                service.finishOrder(buffer);
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strcmp(buffer, "accept_payment") == 0) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            double amount;
            ss >> amount;
            ss.ignore(1);
            try {
                service.acceptPayment(buffer, amount);
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else {
            std::cout << "Unknown command!" << std::endl;
            continue;
        }
    }
}