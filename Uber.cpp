#include "Uber.h"
#include <sstream>
#include <cstring>

const int BUFFER_SIZE = 100;

void Uber::load() {

}

void Uber::save() {

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
    if(activeUser == nullptr) {
        throw std::runtime_error("You can't logout, because you aren't logged in!");
    }
    activeUser = nullptr;
    std::cout << "Logout successful!" << std::endl;
}

void Uber::whoami() const {
    std::cout << "User: " << activeUser->getUsername();
}
