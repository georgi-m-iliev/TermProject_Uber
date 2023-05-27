#include "Uber.h"
#include <sstream>
#include <cstring>
#include <fstream>

const int BUFFER_SIZE = 100;

void Uber::readUsers(const char* filepath) {
    std::ifstream ifs(filepath, std::ios::in);
    if(!ifs.is_open()) {
        throw std::runtime_error("Users file couldn't be opened! Continuing without user data!");
    }
    char buffer[BUFFER_SIZE * 10];
    // read the heading of file, as we don't need it!
    ifs.getline(buffer, BUFFER_SIZE * 10);
    while(!ifs.eof()) {
        ifs.getline(buffer, BUFFER_SIZE * 10);
        std::stringstream ss(buffer);
        ss.getline(buffer, BUFFER_SIZE, ',');
        if(strcmp(buffer, "0") == 0) {
            //this is client
            static char* messages[] = {(char*)"username", (char*)"password",
                                       (char*)"firstName", (char*)"lastName"};
            char buffer2[sizeof(messages) / sizeof(char*)][BUFFER_SIZE];
            for(int i = 0; i < sizeof(messages) / sizeof(char*); i++) {
                ss.getline(buffer2[i], BUFFER_SIZE, ',');
                if(ss.eof()) {
                    throw std::runtime_error("Not enough data!");
                }
            }
            Client client;
            client.setUsername(buffer2[0]);
            client.setPasswordHash(buffer2[1]);
            client.setFirstName(buffer2[2]);
            client.setLastName(buffer2[3]);
            size_t value;
            ss >> value;
            client.setBalance(value);
            if(!ss.eof()) {
                throw std::runtime_error("Invalid file!");
            }
            users.push_back(SharedPtr<User>(new Client(std::move(client))));
        }
        else if(strcmp(buffer, "1") == 0) {
            //this is driver
            static char* messages[] = {(char*)"username", (char*)"password",
                                       (char*)"firstName", (char*)"lastName",
                                       (char*)"carNumber", (char*)"phoneNumber"};
            char buffer2[sizeof(messages) / sizeof(char*)][BUFFER_SIZE];
            for(int i = 0; i < sizeof(messages) / sizeof(char*); i++) {
                ss.getline(buffer2[i], BUFFER_SIZE, ',');
                if(ss.eof()) {
                    throw std::runtime_error("Row consists of incomplete data!");
                }
            }
            Driver driver;
            driver.setUsername(buffer2[0]);
            driver.setPasswordHash(buffer2[1]);
            driver.setFirstName(buffer2[2]);
            driver.setLastName(buffer2[3]);
            size_t balance;
            ss >> balance;
            ss.ignore(1, ',');
            driver.setCarNumber(buffer2[4]);
            driver.setPhoneNumber(buffer2[5]);
            double rating;
            ss >> rating;
            driver.setRating(rating);
            if(!ss.eof()) {
                throw std::runtime_error("Row consists of too much data!");
            }
            users.push_back(SharedPtr<User>(new Driver(std::move(driver))));
        }
    }
    ifs.close();
}


void Uber::readOrders(const char* filepath, vector<SharedPtr<Order>>& col) {
    std::ifstream ifs(filepath, std::ios::in);
    if(!ifs.is_open()) {
        throw std::runtime_error("Orders file couldn't be opened! Continuing without user data!");
    }

    char buffer[BUFFER_SIZE];
    // read the heading of file, as we don't need it!
    ifs.getline(buffer, BUFFER_SIZE);
    while(!ifs.eof()) {
        ifs.getline(buffer, BUFFER_SIZE);
        std::stringstream ss(buffer);
        char* messages[] = {(char*)"id", (char*)"status", (char*)"clientUsername", (char*)"driverUsername",
                          (char*)"address", (char*)"destination", (char*)"passengers", (char*)"amount"};
        char buffer2[3][BUFFER_SIZE];
        Location l1, l2; //4, 5
        short status, passengers; // 1,6
        size_t amount; //7
        const Client* client;
        const Driver* driver;
        for(int i = 0, j = 0; i < sizeof(messages) / sizeof(char*); i++) {
            switch(i) {
                case 1:
                    ss >> status;
                    ss.ignore(1, ',');
                    break;
                case 4:
                    ss >> l1;
                    ss.ignore(1, ',');
                    break;
                case 5:
                    ss >> l2;
                    ss.ignore(1, ',');
                    break;
                case 6:
                    ss >> passengers;
                    ss.ignore(1, ',');
                    break;
                case 7:
                    ss >> amount;
                    ss.ignore(1, ',');
                default:
                    ss.getline(buffer2[j++], BUFFER_SIZE, ',');
            }
        }
        for(int k = 0; k < users.getSize(); k++) {
            if(strcmp(users[k]->getUsername().c_str(), buffer2[1]) == 0) {
                client = (Client*)&users[k];
            }
            else if(strcmp(users[k]->getUsername().c_str(), buffer2[2]) == 0) {
                driver = (Driver*)&users[k];
            }
        }
        col.push_back(SharedPtr<Order>(new Order(buffer2[1], (OrderStatus)status, client, driver, l1, l2, passengers, amount)));
    }

    ifs.close();
}

void Uber::load() {
    try {
        readUsers(R"(D:\Workspace\FMI\OOP_TermProject_Uber\users.csv)");
    }
    catch(std::exception& ex) {
        if(strstr(ex.what(), "File couldn't be opened!") == ex.what()) {
            std::cout << ex.what();
        }
        else if(strcmp(ex.what(), "Row consists of incomplete data!") == 0) {
            std::cout << "FIle isn't complete!";
        }
        else if(strcmp(ex.what(), "Row consists of too much data!") == 0) {

        }
        else {
            std::cout << "Loading from file was unsuccessful!" << std::endl;
        }

    }
    try {
        readOrders(R"(D:\Workspace\FMI\OOP_TermProject_Uber\orders.csv)", activeOrders);
    }
    catch(std::exception& ex) {
        if(strstr(ex.what(), "File couldn't be opened!") == ex.what()) {
            std::cout << ex.what();
        }
        else if(strcmp(ex.what(), "Row consists of incomplete data!") == 0) {
            std::cout << "FIle isn't complete!";
        }
        else if(strcmp(ex.what(), "Row consists of too much data!") == 0) {

        }
        else {
            std::cout << "Loading from file was unsuccessful!" << std::endl;
        }

    }
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
        if(strcmp(users[i]->getUsername().c_str(), username) == 0) {
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

            users.push_back(SharedPtr<User>(new Client(buffer[0], buffer[1], buffer[2], buffer[3])));
        } break;
        case UserType::Driver: {
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
            users.push_back(SharedPtr<User>(new Driver(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5])));
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
        if(strcmp(users[i]->getUsername().c_str(), buffer) == 0) {
            //TODO: this is very dirt way of doing this, fix later
            activeUser = users[i].operator->();
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
        switch(i) {
            case 0:
            case 1:{
                std::cin.getline(line, BUFFER_SIZE);
                std::stringstream ss(line);
                int x, y;
                char addressBuffer[2][BUFFER_SIZE] = {};
                ss.getline(addressBuffer[0], BUFFER_SIZE, ' ');
                ss >> x >> y;
                ss.ignore(1);
                if(!ss.eof()) {
                    ss.getline(addressBuffer[1], BUFFER_SIZE);
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
    order.calcID();
    std::cout << order;
    activeOrders.push_back(SharedPtr<Order>(new Order(std::move(order))));
}

void Uber::print() {

}

void Uber::checkOrder(const char* id) {
    checkUserLoggedIn();
    for(int i = 0; i < activeOrders.getSize(); i++) {
        if(strcmp(activeOrders[i]->getID(), id) == 0) {
            if(activeOrders[i]->client != activeUser && activeOrders[i]->driver != activeUser) {
                throw std::runtime_error("You have no access to this order!");
            }
            std::cout << *activeOrders[i];
            return;
        }
    }
    throw std::runtime_error("Order with this ID was not found!");
}

void Uber::cancelOrder(const char* id) {
    checkUserLoggedIn();
    checkActiveUserType(UserType::Client);
    for(int i = 0; i < activeOrders.getSize(); i++) {
        if(strcmp(activeOrders[i]->getID(), id) == 0) {
            if(activeOrders[i]->client != activeUser && activeOrders[i]->driver != activeUser) {
                throw std::runtime_error("You have no access to this order!");
            }
            activeOrders[i]->setStatus(OrderStatus::CANCELED);
            return;
        }
    }
    throw std::runtime_error("Order with this ID was not found!");
}

void Uber::payOrder(const char* id, double levas) {
    checkUserLoggedIn();
    checkActiveUserType(UserType::Client);
}

void Uber::rateOrder(const char* id, short rating) {
    checkUserLoggedIn();
    checkActiveUserType(UserType::Client);
}

void Uber::addMoney(double levas) {
    checkUserLoggedIn();
    checkActiveUserType(UserType::Client);
    ((Client*)activeUser)->depositAmount(levas);
}

