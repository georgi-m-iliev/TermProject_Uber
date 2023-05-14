#include <iostream>
#include "Security/SHA256.h"
#include "Utilities/MyString.h"
#include "Users/Client.h"

int main() {
    Client az("georgi", "parola", "Georgi", "Iliev");
//    std::cout << std::boolalpha << az.verifyPassword("parola");
    User* something = &az;
    if(something->getType() == UserType::Client) {
        std::cout << "Client";
    }
    else if(something->getType() == UserType::Driver) {
        std::cout << "Driver";
    }

    return 0;
}