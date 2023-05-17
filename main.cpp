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
                std::cout << ex.what();
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
        else {
            std::cout << "Unknown command!" << std::endl;
            continue;
        }
    }
}