#include "Uber.h"
#include <sstream>
#include <cstring>
#include <fstream>
#include <limits>

const int BUFFER_SIZE = 256;

void Uber::readUsers(const char* filepath) {
    std::ifstream ifs(filepath, std::ios::in);
    if(!ifs.is_open()) {
        throw std::runtime_error("File couldn't be opened!");
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
            [[maybe_unused]] static char* messages[] = {
                (char*)"username", (char*)"password",(char*)"firstName", (char*)"lastName", (char*)"amount"
            };
            char buffer2[sizeof(messages) / sizeof(char*) - 1][BUFFER_SIZE];
            size_t amount;

            for(int i = 0; i < sizeof(messages) / sizeof(char*); i++) {
                if(ss.eof()) {
                    throw std::runtime_error("Row consists of incomplete data!");
                }
                switch(i) {
                    case 4:
                        ss >> amount;
                        break;
                    default:
                        ss.getline(buffer2[i], BUFFER_SIZE, ',');
                }
            }
            if(!ss.eof()) {
                throw std::runtime_error("Row consists of too much data!");
            }

            Client client;
            client.setUsername(buffer2[0]);
            client.setPasswordHash(buffer2[1]);
            client.setFirstName(buffer2[2]);
            client.setLastName(buffer2[3]);
            client.setBalanceNom(amount);
            users.push_back(ObjPtr<User>(new Client(std::move(client))));
        }
        else if(strcmp(buffer, "1") == 0) {
            //this is driver
            [[maybe_unused]] static char* messages[] = {(char*)"username", (char*)"password",
                                       (char*)"firstName", (char*)"lastName", (char*)"amount",
                                       (char*)"carNumber", (char*)"phoneNumber", (char*)"rating", (char*)"availability"};
            char buffer2[sizeof(messages) / sizeof(char*) - 3][BUFFER_SIZE];
            size_t balance;
            double rating;
            bool availability;

            for(int i = 0, j = 0; i < sizeof(messages) / sizeof(char*); i++) {
                if(ss.eof()) {
                    throw std::runtime_error("Row consists of incomplete data!");
                }
                switch(i) {
                    case 4:
                        ss >> balance;
                        ss.ignore(1, ',');
                        break;
                    case 7:
                        ss >> rating;
                        ss.ignore(1, ',');
                        break;
                    case 8:
                        ss >> availability;
                    default:
                        ss.getline(buffer2[j++], BUFFER_SIZE, ',');
                }
            }
            if(!ss.eof()) {
                throw std::runtime_error("Row consists of too much data!");
            }

            Driver driver;
            driver.setUsername(buffer2[0]);
            driver.setPasswordHash(buffer2[1]);
            driver.setFirstName(buffer2[2]);
            driver.setLastName(buffer2[3]);
            driver.setBalance(balance);
            driver.setCarNumber(buffer2[4]);
            driver.setPhoneNumber(buffer2[5]);
            driver.setRating(rating);

            users.push_back(ObjPtr<User>(new Driver(std::move(driver))));
        }
    }

    ifs.close();
}

void Uber::readOrders(const char* filepath, vector<Order>& col, bool addNet) {
    std::ifstream ifs(filepath, std::ios::in);
    if(!ifs.is_open()) {
        throw std::runtime_error("File couldn't be opened!");
    }

    char buffer[BUFFER_SIZE];
    // read the heading of file, as we don't need it!
    ifs.getline(buffer, BUFFER_SIZE);
    while(!ifs.eof()) {
        ifs.getline(buffer, BUFFER_SIZE);
        std::stringstream ss(buffer);
        char* messages[] = {(char*)"id", (char*)"status", (char*)"clientUsername", (char*)"driverUsername",
                          (char*)"address", (char*)"destination", (char*)"passengers", (char*)"minutes",(char*)"amount"};
        char buffer2[sizeof(messages) / sizeof(char*) - 6][BUFFER_SIZE];
        Location l1, l2; //4, 5
        short status, passengers, minutes; // 1,6,7
        size_t amount; //7
        Client* client = nullptr;
        Driver* driver = nullptr;
        for(int i = 0, j = 0; i < sizeof(messages) / sizeof(char*); i++) {
            if(ss.eof()) {
                throw std::runtime_error("Row consists of incomplete data!");
            }
            switch(i) {
                case 1:
                    ss >> status;
                    ss.ignore(1, ',');
                    break;
                case 4:
                    ss >> l1;
//                    ss.ignore(1, ',');
                    break;
                case 5:
                    ss >> l2;
//                    ss.ignore(1, ',');
                    break;
                case 6:
                    ss >> passengers;
                    ss.ignore(1, ',');
                    break;
                case 7:
                    ss >> minutes;
                    ss.ignore(1, ',');
                    break;
                case 8:
                    ss >> amount;
                    ss.ignore(1, ',');
                    break;
                default:
                    ss.getline(buffer2[j++], BUFFER_SIZE, ',');
            }
        }
        if(!ss.eof()) {
            throw std::runtime_error("Row consists of too much data!");
        }
        if(strcmp(buffer2[2], "NULL") == 0) {
            driver = nullptr;
        }
        for(int k = 0; k < users.getSize(); k++) {
            if(strcmp(users[k]->getUsername().c_str(), buffer2[1]) == 0) {
                client = dynamic_cast<Client*>(&*users[k]); // it is desired to be nullptr, if for some reason a user is of wrong kind
            }
            else if(strcmp(buffer2[2], "NULL") != 0 && strcmp(users[k]->getUsername().c_str(), buffer2[2]) == 0) {
                driver = dynamic_cast<Driver*>(&*users[k]); // it is desired to be nullptr, if for some reason a user is of wrong kind
            }
        }
        if(addNet) {
            netEarnings += (double)amount / 100.0;
        }
        col.push_back(Order(buffer2[0], (OrderStatus)status, client, driver, l1, l2, passengers, minutes, amount));
    }

    ifs.close();
}

void Uber::load() {
    try {
        readUsers((path + "users.csv").c_str());
    }
    catch(std::exception& ex) {
        std::cout << "Problem with users file!" << " ";
        if(strstr(ex.what(), "File couldn't be opened!") == ex.what()) {
            std::cout << ex.what();
        }
        else if(strstr(ex.what(), "Row consists") == ex.what()) {
            std::cout << "File is broken!";
        }
        else {
            std::cout << "Loading from file was unsuccessful!";
        }
        std::cout << " " << "Continuing without saved users!" << std::endl;
    }
    try {
        readOrders((path + "active_orders.csv").c_str(), activeOrders, false);
        readOrders((path + "finished_orders.csv").c_str(), finishedOrders, true);
    }
    catch(std::exception& ex) {
        std::cout << "Problem with orders file!" << " ";
        if(strstr(ex.what(), "File couldn't be opened!") == ex.what()) {
            std::cout << ex.what();
        }
        else if(strstr(ex.what(), "Row consists") == ex.what()) {
            std::cout << "File is broken!";
        }
        else {
            std::cout << "Loading from file was unsuccessful!";
        }
        std::cout << " " << "Continuing without saved orders!" << std::endl;
        activeOrders.clear();
        finishedOrders.clear();
    }
}

void Uber::saveUsers(const char* filepath) {
    std::ofstream ofs(filepath, std::ios::out | std::ios::trunc);
    if(!ofs.is_open()) {
        throw std::runtime_error("File couldn't be opened!");
    }

    ofs << "type,username,password_hash,first_name,last_name,amount,car_number,phone_number,rating,availability";

    for(size_t i = 0; i < users.getSize(); i++) {
        ofs << '\n';
        ofs << (int)users[i]->getType() << ',';
        ofs << users[i]->getUsername() << ',';
        ofs << users[i]->getPasswordHash() << ',';
        ofs << users[i]->getFirstName() << ',';
        ofs << users[i]->getLastName() << ',';
        ofs << users[i]->getBalanceNom();

        if(users[i]->getType() == UserType::Driver) {
            ofs << ',';
            ofs << static_cast<Driver*>(&*users[i])->getCarNumber() << ',';
            ofs << static_cast<Driver*>(&*users[i])->getPhoneNumber() << ',';
            ofs << static_cast<Driver*>(&*users[i])->getRating();
            ofs << static_cast<Driver*>(&*users[i])->isAvailable();
        }
    }

    ofs.close();
}

void Uber::saveOrders(const char* filepath, vector<Order>& col) {
    std::ofstream ofs(filepath, std::ios::out | std::ios::trunc);
    if(!ofs.is_open()) {
        throw std::runtime_error("File couldn't be opened!");
    }

    ofs << "id,status,clientUsername,driverUsername,address,destination,passengers,minutes,amount";
    for(size_t i = 0; i < col.getSize(); i++) {
        ofs << '\n';
        ofs << col[i].getID() << ',';
        ofs << (int)col[i].getStatus() << ',';
        ofs << col[i].getClient()->getUsername() << ',';
        if(col[i].getDriver()) {
            ofs << col[i].getDriver()->getUsername() << ',';
        }
        else {
            ofs << "NULL" << ',';
        }
        ofs << col[i].getAddress().getName() << " " << col[i].getAddress().getPoint().x << " " << col[i].getAddress().getPoint().y <<  ',';
        ofs << col[i].getDestination().getName() << " " << col[i].getDestination().getPoint().x << " " << col[i].getDestination().getPoint().y <<  ',';
        ofs << col[i].getPassengers() << ',';
        ofs << col[i].getMinutes() << ',';
        ofs << col[i].getAmount();
    }

    ofs.close();
}

void Uber::save() {
    try {
        saveUsers((path + "users.csv").c_str());
    }
    catch(std::exception& ex) {
        std::cout << "Problem with saving users!" << " ";
        if(strstr(ex.what(), "File couldn't be opened!") == ex.what()) {
            std::cout << ex.what();
        }
        else {
            std::cout << "Saving from file was unsuccessful!";
        }
    }
    try {
        saveOrders((path + "active_orders.csv").c_str(), activeOrders);
        saveOrders((path + "finished_orders.csv").c_str(), finishedOrders);
    }
    catch(std::exception& ex) {
        std::cout << "Problem with saving orders!" << " ";
        if(strstr(ex.what(), "File couldn't be opened!") == ex.what()) {
            std::cout << ex.what();
        }
        else {
            std::cout << "Saving from file was unsuccessful!";
        }
    }
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
    for(size_t i = 0; i < users.getSize(); i++) {
        if(strcmp(users[i]->getUsername().c_str(), username) == 0) {
            return true;
        }
    }
    return false;
}

Order& Uber::findOrder(const char* id) {
    for(size_t i = 0; i < activeOrders.getSize(); i++) {
        if(strcmp(activeOrders[i].getID(), id) == 0) {
            return activeOrders[i];
        }
    }
    for(size_t i = 0; i < finishedOrders.getSize(); i++) {
        if(strcmp(finishedOrders[i].getID(), id) == 0) {
            return finishedOrders[i];
        }
    }
    throw std::runtime_error("Order with this ID was not found!");
}

const Order& Uber::findOrder(const char* id) const {
    for(size_t i = 0; i < activeOrders.getSize(); i++) {
        if(strcmp(activeOrders[i].getID(), id) == 0) {
            return activeOrders[i];
        }
    }
    for(size_t i = 0; i < finishedOrders.getSize(); i++) {
        if(strcmp(finishedOrders[i].getID(), id) == 0) {
            return finishedOrders[i];
        }
    }
    throw std::runtime_error("Order with this ID was not found!");
}

void Uber::moveOrderToFinished(const char* id) {
    size_t ind = 0;
    for(size_t i = 0; i < activeOrders.getSize(); i++) {
        if(strcmp(activeOrders[i].getID(), id) == 0) {
            ind = i;
            break;
        }
        if(ind == 0 && i == activeOrders.getSize() - 1) {
            throw std::runtime_error("Order with this ID was not found!");
        }
    }
    activeOrders[ind].clearDriversDeclined();
    finishedOrders.push_back(std::move(activeOrders[ind]));
    activeOrders.pop_at(ind);
}

void Uber::handoutOrders() {
    for(size_t i = 0; i < activeOrders.getSize(); i++) {
        if(activeOrders[i].getStatus() != OrderStatus::CREATED || activeOrders[i].getDriver() != nullptr) {
            continue;
        }
        double minDistance = std::numeric_limits<double>::max();
        int minInd = -1;
        for(int j = 0; j < users.getSize(); j++) {
            if(users[j]->getType() == UserType::Client || !dynamic_cast<Driver&>(*users[j]).isAvailable()) {
                continue;
            }
            if(activeOrders[i].hasDeclined(&*users[j])) {
                continue;
            }
            double currentDistance = distanceBtwn(activeOrders[i].getAddress(), static_cast<Driver*>(&*users[j])->getCurrentLocation());
            if(currentDistance < minDistance) {
                minDistance = currentDistance;
                minInd = j;
            }
        }
        if(minInd == -1) {
            continue;
        }
        activeOrders[i].setDriver(static_cast<Driver*>(&*users[minInd]));
        activeOrders[i].setStatus(OrderStatus::AWAITING_DRIVER);
    }
}

Uber::Uber(): Uber(DEFAULT_PATH) {
    activeUser = nullptr;
    netEarnings = 0;
}

Uber::Uber(const char* path): activeUser(nullptr), path(path) {
    load();
}

Uber::Uber(const Uber& other): path(other.path), users(other.users), activeOrders(other.activeOrders), finishedOrders(other.finishedOrders)     {
    activeUser = nullptr;
}

Uber::~Uber() {
    save();
}

void Uber::print() {
    checkUserLoggedIn();
    checkActiveUserType(UserType::Driver);
    std::cout << "Company Net Earnings: " << netEarnings << std::endl;
    for(size_t i = 0; i < activeOrders.getSize(); i++) {
        std::cout << activeOrders[i] << std::endl;
    }
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

            users.push_back(ObjPtr<User>(
                    new Client(buffer[0], buffer[1], buffer[2], buffer[3])
            ));
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
            users.push_back(ObjPtr<User>(
                new Driver(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5])
            ));
        } break;
    }
    std::cout << "Successful registration! Please login to access the app!" << std::endl;
}

void Uber::loginUser(std::stringstream& ss) {
    if(activeUser != nullptr) {
        throw std::runtime_error("You cannot login, because you are already logged in!");
    }
    // potentialUser is going to hold the pointer to the actual user, until we are sure the login is successful,
    // if we assign it to activeUser at the beginning, there is a possibility of something going wrong before password
    // verification has finished, leaving us successfully authenticated with possibly wrong password.
    User* potentialUser = nullptr;
    char buffer[BUFFER_SIZE];
    ss.getline(buffer, BUFFER_SIZE, ' ');
    for(size_t i = 0; i < users.getSize(); i++) {
        if(strcmp(users[i]->getUsername().c_str(), buffer) == 0) {
            potentialUser = &*users[i];
        }
    }

    if(potentialUser == nullptr) {
        throw std::invalid_argument("No user under this username!");
    }

    ss.getline(buffer, BUFFER_SIZE, ' ');
    if(!potentialUser->verifyPassword(buffer)) {
        throw std::invalid_argument("Wrong password!");
    }
    std::cout << "Login successful!" << std::endl;
    activeUser = potentialUser;
//    if(dynamic_cast<Driver*>(&*activeUser)) {
//        checkMessages();
//    }
}

void Uber::logoutUser() {
    checkUserLoggedIn("You can't logout, because you aren't logged in!");
    activeUser = nullptr;
    std::cout << "Logout successful!" << std::endl;
}

void Uber::changePassword(const char* password) {
    checkUserLoggedIn();
    activeUser->setPassword(password);
    std::cout << "Password changes successfully!";
}

void Uber::whoami() const {
    checkUserLoggedIn();
    std::cout << "User: " << activeUser->getUsername() << " -> "
                << (activeUser->getType() == UserType::Client ? "Client" : "Driver") << std::endl;
}

void Uber::listOrders() const {
    checkUserLoggedIn();
    std::cout << std::endl <<  "-------Orders associated with current user!-------" << std::endl;
    switch(activeUser->getType()) {
        case UserType::Client:
            for(size_t i = 0, counter = 0; i < activeOrders.getSize(); i++) {
                if(activeOrders[i].getClient() == activeUser) {
                    std::cout << (++counter) << "." << activeOrders[i].getID() << std::endl;
                }
            }
            break;
        case UserType::Driver:
            for(size_t i = 0, counter = 0; i < activeOrders.getSize(); i++) {
                if(activeOrders[i].getDriver() == activeUser && activeOrders[i].getStatus() > OrderStatus::ACCEPTED_BY_DRIVER && activeOrders[i].getStatus() < OrderStatus::AWAITING_RATING) {
                    std::cout << (++counter) << "." << activeOrders[i].getID() << std::endl;
                }
            }
            break;
    }
}

void Uber::order() {
    checkUserLoggedIn();
    checkActiveUserType(UserType::Client);

    Order order;
    static char *messages[] = {(char*)"Address?", (char*)"Destination?", (char*)"Number of passengers?"};
    char line[BUFFER_SIZE];
    for(int i = 0; i < sizeof(messages) / sizeof(char*); i++) {
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
    std::cout << order;
    activeOrders.push_back(std::move(order));
}

void Uber::checkOrder(const char* id) const {
    checkUserLoggedIn();
    const Order& order = findOrder(id);
    if(order.getClient() != activeUser && order.getDriver() != activeUser) {
        throw std::runtime_error("You have no access to this order or action unavailable!");
    }
    std::cout << std::endl << order;
    switch(activeUser->getType()) {
        case UserType::Client: {
            if(order.getDriver() == nullptr && order.getStatus() <= OrderStatus::AWAITING_DRIVER) {
                return;
            }
            std::cout << "Driver: " << order.getDriver()->getFirstName() << " " << order.getDriver()->getLastName()
                      << std::endl;
            std::cout << "Car Number: " << order.getDriver()->getCarNumber() << std::endl;
            std::cout << "Phone: " << order.getDriver()->getPhoneNumber() << std::endl;
        } break;
        case UserType::Driver: {
            std::cout << "Client: " << order.getClient()->getFirstName() << " " << order.getClient()->getLastName() << std::endl;
        } break;
    }
}

void Uber::cancelOrder(const char* id) {
    checkUserLoggedIn();
    checkActiveUserType(UserType::Client);

    Order& order = findOrder(id);
    if(order.getClient() != activeUser && order.getDriver() != activeUser) {
        throw std::runtime_error("You have no access to this order or action unavailable!");
    }
    if(order.getStatus() > OrderStatus::ACCEPTED_BY_DRIVER) {
        throw std::runtime_error("You can't cancel your order anymore!");
    }
    order.setStatus(OrderStatus::CANCELED);
    if(order.getDriver() != nullptr) {
        order.getDriver()->setAvailability(true);
    }
    std::cout << "Order has been canceled!" << std::endl;
}

void Uber::payOrder(const char* id, double levas) {
    checkUserLoggedIn();
    checkActiveUserType(UserType::Client);

    if(activeUser->getBalance() < (size_t)(levas * 100)) {
        throw std::runtime_error("You don't have enough balance to pay this order!\nPlease use the deposit functionality!");
    }

    Order& order = findOrder(id);
    if(order.getClient() != activeUser) {
        throw std::runtime_error("You have no access to this order or action unavailable!");
    }
    if(order.getStatus() != OrderStatus::DESTINATION_REACHED) {
        throw std::runtime_error("You can't pay at this moment!");
    }
    if(order.getAmountNom() != (size_t)(levas * 100)) {
        throw std::invalid_argument("The order amount is not the same as the pay amount!");
    }
    order.setStatus(OrderStatus::PAID);
    order.getClient()->withdrawAmount(levas);
    order.getDriver()->depositAmount(levas);
    netEarnings += order.getAmount();

    std::cout << "Order paid successfully!" << std::endl;
}

void Uber::rateOrder(const char* id, short rating) {
    checkUserLoggedIn();
    checkActiveUserType(UserType::Client);

    if(rating < 0 || rating > 5) {
        throw std::invalid_argument("Rating can range from 0 to 5!");
    }

    Order& order = findOrder(id);
    if(order.getClient() != activeUser) {
        throw std::runtime_error("You have no access to this order or action unavailable!");
    }
    if(order.getStatus() != OrderStatus::AWAITING_RATING) {
        throw std::runtime_error("You can't rate this order at this moment!");
    }
    order.rateDriver(rating);
    order.setStatus(OrderStatus::FINISHED);
    moveOrderToFinished(order.getID());
    std::cout << "Order rated successfully!" << std::endl;
}

void Uber::addMoney(double amount) {
    if(amount <= 0) {
        throw std::invalid_argument("Invalid value specified!");
    }
    checkUserLoggedIn();
    checkActiveUserType(UserType::Client);
    ((Client*) activeUser)->depositAmount(amount);
    std::cout << "The deposit of " << amount << " was successful!" << std::endl;
}

void Uber::changeAddress(std::stringstream& ss) {
    checkUserLoggedIn();
    checkActiveUserType(UserType::Driver);

    [[maybe_unused]] static char *messages[] = {(char*)"Name?", (char*)"X?", (char*)"Y?"};
    char name[BUFFER_SIZE];
    int x, y;
    for(int i = 0; i < sizeof(messages) / sizeof(char*); i++) {
        if(ss.eof()) {
            throw std::runtime_error("Command syntax invalid!");
        }
        switch(i) {
            case 0:
                ss.getline(name, BUFFER_SIZE, ' ');
                break;
            case 1:
                ss >> x;
                ss.ignore(1);
                break;
            case 2:
                ss >> y;
                ss.ignore(1);
                break;
        }
    }
    if(!ss.eof()) {
        throw std::runtime_error("Command syntax invalid!");
    }

    static_cast<Driver*>(activeUser)->setCurrentLocation(name, x, y);
    std::cout << "Location changes successfully!" << std::endl;
}

void Uber::checkMessages() {
    checkUserLoggedIn();
    checkActiveUserType(UserType::Driver);
    handoutOrders();
    std::cout << std::endl <<  "-----------Driver messages from System!-----------" << std::endl;
    bool empty = true;
    for(size_t i = 0; i < activeOrders.getSize(); i++) {
        if(activeOrders[i].getStatus() == OrderStatus::AWAITING_DRIVER && activeOrders[i].getDriver() == activeUser) {
            std::cout << "Client: "
                << activeOrders[i].getClient()->getFirstName() << " " << activeOrders[i].getClient()->getLastName() << std::endl;
            std::cout << activeOrders[i] << std::endl;
            empty = false;
        }
    }
    if(empty) {
        std::cout << "                 No new messages!                 " << std::endl;
    }
}

void Uber::acceptOrder(const char* id, short minutes, double amount) {
    checkUserLoggedIn();
    checkActiveUserType(UserType::Driver);
    handoutOrders();

    Order& order = findOrder(id);
    if(order.getStatus() != OrderStatus::AWAITING_DRIVER || order.getDriver() != activeUser) {
        throw std::runtime_error("You have no access to this order or action unavailable!");
    }
    order.setStatus(OrderStatus::ACCEPTED_BY_DRIVER);
    order.setAmount(amount);
    order.setMinutes(minutes);
    static_cast<Driver*>(activeUser)->setAvailability(false);
    std::cout << "Order accepted successfully!" << std::endl;
}

void Uber::declineOrder(const char* id) {
    checkUserLoggedIn();
    checkActiveUserType(UserType::Driver);

    Order& order = findOrder(id);
    if(order.getStatus() > OrderStatus::ACCEPTED_BY_DRIVER || order.getDriver() != activeUser) {
        throw std::runtime_error("You have no access to this order or action unavailable!");
    }
    order.setStatus(OrderStatus::CREATED);
    order.setAmount(0);
    order.setMinutes(0);
    order.setDriver(nullptr);
    order.addDriverDeclined(activeUser);
    static_cast<Driver*>(activeUser)->setAvailability(true);
    std::cout << "Order declined successfully!" << std::endl;
    handoutOrders();
}

void Uber::pickupPassenger(const char* id) {
    checkUserLoggedIn();
    checkActiveUserType(UserType::Driver);

    Order& order = findOrder(id);
    if(order.getStatus() != OrderStatus::ACCEPTED_BY_DRIVER || order.getDriver() != activeUser) {
        throw std::runtime_error("You have no access to this order or action unavailable!");
    }
    order.setStatus(OrderStatus::PASSENGER_PICKEDUP);
    static_cast<Driver*>(activeUser)->setCurrentLocation(order.getAddress());
    std::cout << "Passenger picked up recorded!" << std::endl;
}

void Uber::finishOrder(const char* id) {
    checkUserLoggedIn();
    checkActiveUserType(UserType::Driver);

    Order& order = findOrder(id);
    if(order.getStatus() != OrderStatus::PASSENGER_PICKEDUP || order.getDriver() != activeUser) {
        throw std::runtime_error("You have no access to this order or action unavailable!");
    }
    order.setStatus(OrderStatus::DESTINATION_REACHED);
    static_cast<Driver*>(activeUser)->setCurrentLocation(order.getDestination());
    static_cast<Driver*>(activeUser)->setAvailability(true);
    std::cout << "Order finished successfully!" << std::endl;
}

void Uber::acceptPayment(const char* id, double amount) {
    checkUserLoggedIn();
    checkActiveUserType(UserType::Driver);

    Order& order = findOrder(id);
    if(order.getStatus() != OrderStatus::PAID || order.getDriver() != activeUser) {
        throw std::runtime_error("You have no access to this order or action unavailable!");
    }
    if(order.getAmountNom() != (size_t)(amount * 100)) {
        throw std::invalid_argument("Invalid amount specified!");
    }
    order.setStatus(OrderStatus::AWAITING_RATING);
    std::cout << "Order payment accepted successfully!" << std::endl;
}
