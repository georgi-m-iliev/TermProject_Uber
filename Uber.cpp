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


bool Uber::checkUserExist(const char* username) const {
    for(int i = 0; i < users.getSize(); i++) {
        if(strcmp(users[i].getUsername().c_str(), username) == 0) {
            return true;
        }
    }
    return false;
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
//            Client client;
            [[maybe_unused]] static char* messages[] = {(char*)"Username?", (char*)"Password?",
                                       (char*)"First name?", (char*)"First name?"};
            char buffer[sizeof(messages) / sizeof(char*)][BUFFER_SIZE];

            for(auto & i : buffer) {
                if(ss.eof()) {
                    throw std::runtime_error("You didn't supply all the needed data!");
                }
                ss.getline(i, BUFFER_SIZE, ' ');
            }
            if(!ss.eof()) {
                throw std::runtime_error("You have provided more than the needed data!");
            }

            if(checkUserExist(buffer[0])) {
                throw std::runtime_error("User with the same username already exists!");
            }
//            client.setUsername(buffer[0]);
//            client.setPassword(buffer[1]);
//            client.setFirstName(buffer[2]);
//            client.setLastName(buffer[3]);

            users.move(Client(buffer[0], buffer[1], buffer[2], buffer[3]));
        } break;
        case UserType::Driver: {
//            Driver driver;
            [[maybe_unused]] static char* messages[] = {(char*)"Username?", (char*)"Password?",
                                       (char*)"First name?", (char*)"First name?",
                                       (char*)"Car number?", (char*)"Phone number?"};
            char buffer[sizeof(messages) / sizeof(char*)][BUFFER_SIZE];

            for(auto & i : buffer) {
                if(ss.eof()) {
                    throw std::runtime_error("You didn't supply all the needed data!");
                }
                ss.getline(i, BUFFER_SIZE, ' ');
            }
            if(!ss.eof()) {
                throw std::runtime_error("You have provided more than the needed data!");
            }

            if(checkUserExist(buffer[0])) {
                throw std::runtime_error("User with the same username already exists!");
            }
//            driver.setUsername(buffer[0]);
//            driver.setPassword(buffer[1]);
//            driver.setFirstName(buffer[2]);
//            driver.setLastName(buffer[3]);
//            driver.setCarNumber(buffer[4]);
//            driver.setPhoneNumber(buffer[5]);

            users.move(Driver(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5]));
        } break;
    }
    std::cout << "Successful registration! Please login to access the app!" << std::endl;
}

void Uber::loginUser(std::stringstream& ss) {
    if(activeUser != nullptr) {
        throw std::runtime_error("You cannot login, because you are already logged in!");
    }

    char buffer[BUFFER_SIZE];
    ss.getline(buffer, BUFFER_SIZE, ' ');
    for(int i = 0; i < users.getSize(); i++) {
        if(strcmp(users[i].getUsername().c_str(), buffer) == 0) {
            //TODO: this is very dirt way of doing this, fix later
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
    char line[BUFFER_SIZE];
    for(int i = 0; i < 3; i++) {
        std::cout << "    " << messages[i] << " > ";
        std::cin.getline(line, BUFFER_SIZE);
        std::stringstream ss(line);

        switch(i) {
            case 0:
            case 1:{
                int x, y;
                char addressBuffer[2][MAX_LENGTH] = {};
                ss.getline(addressBuffer[0], MAX_LENGTH, ' ');
                ss >> x >> y;
                ss.ignore(1);
                std::cout << "is it eof?: " << std::boolalpha << ss.eof() << std::endl;
                if(!ss.eof()) {
                    ss.getline(addressBuffer[1], MAX_LENGTH);
                }
                else {
                    addressBuffer[1][0] = '\0';
                }
                switch(i) {
                    case 0:
                        order.setAddress(addressBuffer[0], x, y, addressBuffer[1]);
                        break;
                    case 1:
                        order.setDestination(addressBuffer[0], x, y, addressBuffer[1]);
                        break;
                    //This code in unreachable but the stupid IDE keeps on complaining lol
                    default:
                        throw std::logic_error("Uncovered logic path! Programmer error!");
                }
            } break;
            case 2: {
                short passengerCount;
                std::cin >> passengerCount;
                std::cin.ignore(1);
                order.setPassengers(passengerCount);
            } break;
            default:
                throw std::logic_error("Uncovered logic path! Programmer error!");
        }
    }

    order.setClient((Client*)activeUser);
    order.setStatus(OrderStatus::CREATED);
    std::cout << order.getID() << std::endl;
    activeOrders.move(std::move(order));
}

void Uber::print() {
    std::cout << activeOrders[0].getAddress();
    std::cout << activeOrders[0].getDestination();
    std::cout << activeOrders[0].getPassengers() << std::endl;
}
