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
        else {
            std::cout << std::endl << "DEBUG: " << ss.str() << std::endl;
            bool idk = (bool)ss.getline(buffer, BUFFER_SIZE, ' ');
            std::cout << std::boolalpha << ss.eof() << std::endl;
            std::cout << "Unknown command!" << std::endl;
            continue;
        }
    }
}