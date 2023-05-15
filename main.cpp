#include <iostream>
#include <cstring>
#include <sstream>
#include "Uber.h"

const int BUFFER_SIZE = 1024;

#include <chrono>

int main() {
//    std::time_t t = std::time(0);   // get time now
//    std::tm* now = std::localtime(&t);
//    std::cout << (now->tm_year + 1900) << '-'
//              << (now->tm_mon + 1) << '-'
//              <<  now->tm_mday
//              << "\n";
//
    size_t sec = std::chrono::system_clock::now().time_since_epoch() / std::chrono::seconds(1);;
    std::cout << sec;

    return 0;
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

        if(strstr(buffer, "register") == buffer) {
            ss.getline(buffer, BUFFER_SIZE, ' ');
            if(strstr(buffer, "client") == buffer) {
                try {
                    service.registerUser(UserType::Client, ss);
                }
                catch(std::exception& ex) {
                    std::cout << ex.what() << std::endl;
                }
            }
            else if(strstr(buffer, "driver") == buffer) {
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
        else if(strstr(buffer, "login") == buffer) {
            try {
                service.loginUser(ss);
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strstr(buffer, "logout") == buffer) {
            try {
                service.logoutUser();
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strstr(buffer, "whoami") == buffer) {
            try {
                service.whoami();
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strstr(buffer, "order") == buffer) {
            try {
                service.order();
            }
            catch(std::exception& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        else if(strstr(buffer, "print") == buffer) {
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