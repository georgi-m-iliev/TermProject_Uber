#include "Uber.h"
#include <sstream>
#include <cstring>

const int BUFFER_SIZE = 100;

void Uber::load() {

}

void Uber::save() {

}

void Uber::checkUserLoggedIn(const char* message) const {
    if(activeUser == nullptr) {
        if(message) {
            throw std::runtime_error(message);
        }
        throw std::runtime_error("You aren't logged in! Action unavailable!");
    }
}

void Uber::checkActiveUserType(const UserType type) const {
    if(activeUser->getType() != type) {
        throw std::runtime_error("User isn't allowed to do that!");
    }
}


Uber::Uber(): activeUser(nullptr) {
    load();
}

Uber::~Uber() {
    save();
}

void Uber::registerUser(const UserType type, std::stringstream& ss) {
    if(activeUser != nullptr) {
        throw std::runtime_error("You cannot register, while being logged in!");
    }

    switch(type) {
        case UserType::Client: {
            Client client;
            char buffer[BUFFER_SIZE];

            ss.getline(buffer, BUFFER_SIZE, ' ');
            client.setUsername(buffer);

            ss.getline(buffer, BUFFER_SIZE, ' ');
            client.setPassword(buffer);

            ss.getline(buffer, BUFFER_SIZE, ' ');
            client.setFirstName(buffer);

            ss.getline(buffer, BUFFER_SIZE, ' ');
            client.setLastName(buffer);

//            std::cout << client;
            users.move(std::move(client));
        } break;
        case UserType::Driver: {
            Driver driver;
            char buffer[BUFFER_SIZE];

            ss.getline(buffer, BUFFER_SIZE, ' ');
            driver.setUsername(buffer);

            ss.getline(buffer, BUFFER_SIZE, ' ');
            driver.setPassword(buffer);

            ss.getline(buffer, BUFFER_SIZE, ' ');
            driver.setFirstName(buffer);

            ss.getline(buffer, BUFFER_SIZE, ' ');
            driver.setLastName(buffer);

            ss.getline(buffer, BUFFER_SIZE, ' ');
            driver.setCarNumber(buffer);

            ss.getline(buffer, BUFFER_SIZE, ' ');
            driver.setPhoneNumber(buffer);

            //std::cout << driver;
            users.move(std::move(driver));
        } break;
    }
}

void Uber::loginUser(std::stringstream& ss) {
    if(activeUser != nullptr) {
        throw std::runtime_error("You cannot login, because you are already logged in!");
    }

    char buffer[BUFFER_SIZE];
    ss.getline(buffer, BUFFER_SIZE, ' ');
    for(int i = 0; i < users.getSize(); i++) {
        if(strcmp(users[i].getUsername().c_str(), buffer) == 0) {
            //TODO: this is very dirt way of doing tдепозhis, fix later
            activeUser = &users[i];
        }
    }

    if(activeUser == nullptr) {
        throw std::invalid_argument("No user under this username!");
    }

    ss.getline(buffer, BUFFER_SIZE, ' ');
    if(!activeUser->verifyPassword(buffer)) {
        activeUser = nullptr;
        throw std::invalid_argument("Wrong password!");
    }
    std::cout << "Login successful!" << std::endl;
}

void Uber::logoutUser() {
    checkUserLoggedIn("You can't logout, because you aren't logged in!");
    activeUser = nullptr;
    std::cout << "Logout successful!" << std::endl;
}

void Uber::whoami() const {
    checkUserLoggedIn();
    std::cout << "User: " << activeUser->getUsername() << std::endl;
}

void Uber::order() {
    checkUserLoggedIn();
    checkActiveUserType(UserType::Client);

    static char *messages[] = {(char*)"Address?", (char*)"Destination?", (char*)"Number of passengers?"};
    Order order;
    for(int i = 0; i < 3; i++) {
        std::cout << "    " << messages[i] << " > ";
        if(i == 2) {
            short passengerCount;
            std::cin >> passengerCount;
            std::cin.ignore(1);
            order.setPassengers(passengerCount);
        }
        else {
            int x, y;
            char buffer[2][MAX_LENGTH];
            std::cin.getline(buffer[0], MAX_LENGTH, ' ');
            std::cin >> x >> y;
            std::cin.ignore(1);
            std::cin.getline(buffer[1], MAX_LENGTH);
            if(i == 0) {
                order.setAddress(buffer[0], x, y, buffer[1]);
            }
            else if(i == 1) {
                order.setDestination(buffer[0], x, y, buffer[1]);
            }
        }
    }
    activeOrders.move(std::move(order));
}

void Uber::print() {
    std::cout << activeOrders[0].getAddress();
    std::cout << activeOrders[0].getDestination();
    std::cout << activeOrders[0].getPassengers() << std::endl;
}
