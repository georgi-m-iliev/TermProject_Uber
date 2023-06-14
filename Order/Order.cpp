#include "Order.h"
#include <cstring>
#include <chrono>


namespace {
    const int BUFFER_SIZE = 512;

    void numToStr(size_t num, char* str, int length) {
        int len = 0;
        size_t copy = num;
        do {
            copy /= 10;
            len++;
            if(len > length) {
                return;
            }
        } while(copy != 0);
        for(int i = len - 1; i >= 0; i--) {
            str[i] = (char)(num % 10 + '0');
            num /= 10;
        }
        str[len] = '\0';
    }
}

void Order::calcID() {
    static time_t EPOCH_START = 1684108800; // moment of partial creation of this app
    static char str[14]; // 99 symbols id would  be enough to make it through at least a thousand years,
                         // epoch will be long dead as so will be this ap
    time_t seconds = std::chrono::system_clock::now().time_since_epoch() / std::chrono::seconds(1);
    seconds -= EPOCH_START;
    numToStr(seconds, str, 14);
    // some character translation to make it more readable and unique
    for(int i = 0; i < strlen(str); i++) {
        if(i % 2 == 0) {
            str[i] += 'A' - '0';
        }
        else if(i % 3 == 0) {
            str[i] += 'f' - '0';
            str[i] -= 2;
            str[i] += std::abs(address.getPoint().x - address.getPoint().y) % 10;
        }
        else {
            str[i] += 'a' - '0';
        }
    }

    this->id = str;
}

Order::Order() {
    status = OrderStatus::EMPTY;
    client = nullptr;
    driver = nullptr;
    passengers = 0;
    amount = 0;
    minutes = -1;
}

Order::Order(const char* addressName, int addressX, int addressY, const char* destinationName, int destinationX,
             int destinationY, short passengers):
                address(addressName, addressX, addressY),
                destination(destinationName, destinationX, destinationY) {
    status = OrderStatus::CREATED;
    this->passengers = passengers;
    minutes = -1;
    calcID();
}

Order::Order(const char* addressName, int addressX, int addressY, const char* addressNote, const char* destinationName,
             int destinationX, int destinationY, const char* destinationNote, short passengers):
                address(addressName, addressX, addressY, addressNote),
                destination(destinationName, destinationX, destinationY, destinationNote) {
    status = OrderStatus::CREATED;
    this->passengers = passengers;
    minutes = -1;
    calcID();
}

Order::Order(const char* id, const OrderStatus status, Client* client, Driver* driver,
             const Location& address, const Location& destination, const short passengers, short minutes, const size_t amount) {
    this->id = id;
    this->status = status;
    this->client = client;
    this->driver = driver;
    this->address = address;
    this->destination = destination;
    this->passengers = passengers;
    this->amount = amount;
    this->minutes = minutes;
}

Order* Order::clone() const {
    return new Order(*this);
}

const char* Order::getID() const {
    return id.c_str();
}

const MyString& Order::getID(bool) const {
    return id;
}

OrderStatus Order::getStatus() const {
    return status;
}

const Client* Order::getClient() const {
    return client;
}

const Driver* Order::getDriver() const {
    return driver;
}

Client* Order::getClient() {
    return client;
}

Driver* Order::getDriver() {
    return driver;
}

const Location& Order::getAddress() const {
    return address;
}

const Location& Order::getDestination() const {
    return destination;
}

short Order::getPassengers() const {
    return passengers;
}

short Order::getMinutes() const {
    return minutes;
}

double Order::getAmount() const {
    return (double)amount / 100.0;
}

size_t Order::getAmountNom() const {
    return (size_t)(amount / 100);
}

void Order::setID(const char* id) {
    this->id = id;
}

void Order::setStatus(OrderStatus status) {
    this->status = status;
}

void Order::setClient(Client* client) {
    this->client = client;
}

void Order::setDriver(Driver* driver) {
    this->driver = driver;
}

void Order::setAddress(const char* name, int x, int y, const char* note) {
    address.setName(name);
    address.setPoint(x, y);
    if(strlen(note) != 0) {
        address.setNote(note);
    }
    calcID();
}


void Order::setAddress(const Location& loc) {
    address = loc;
}

void Order::setDestination(const char* name, int x, int y, const char* note) {
    destination.setName(name);
    destination.setPoint(x, y);
    if(strlen(note) != 0) {
        destination.setNote(note);
    }
}

void Order::setDestination(const Location& loc) {
    destination = loc;
}

void Order::setPassengers(short passengers) {
    this->passengers = passengers;
}

void Order::setMinutes(short minutes) {
    this->minutes = minutes;
}

void Order::setAmount(double amount) {
    this->amount = (size_t)(amount * 100);
}

void Order::setAmountNom(size_t amount) {
    this->amount = amount;
}

void Order::rateDriver(short rating) {
    if(this->driver == nullptr) {
        throw std::logic_error("Can't rate this order!");
    }
    driver->addRating(rating);
}

std::ostream& operator<<(std::ostream& os, const Order& order) {
    std::cout << "---------------====================---------------" << std::endl;
    std::cout << "Order ID: " << order.getID() << std::endl;
    std::cout << "[ " << order.getAddress() << " ] -> [ " << order.getDestination() << " ]" << std::endl;
    std::cout << "Passengers: " << order.getPassengers() << "  Amount: " ;
    if(order.getAmount() == 0) {
        std::cout << "NaN";
    }
    else {
        std::cout << order.getAmount() << " ";
    }
    std::cout << " Waiting time: ";
    if(order.getMinutes() == -1) {
        std::cout << "NaN";
    }
    else {
        std::cout << order.getMinutes();
    }
    std::cout << " minutes" << std::endl;
//    std::cout << "Status: " << (size_t)order.getStatus() << std::endl;
    return os;
}

void Order::addDriverDeclined(const User* user) {
    driversDeclined.push_back(user);
}

bool Order::hasDeclined(const User* user) const {
    for(size_t i = 0; i < driversDeclined.getSize(); i++) {
        if(driversDeclined[i]->getUsername() == user->getUsername()) {
            return true;
        }
    }
    return false;
}

void Order::clearDriversDeclined() {
    driversDeclined.clear();
}

std::istream& Order::read(std::istream& inp, vector<ObjPtr<User>>& users) {
    char* messages[] = {(char*)"id", (char*)"status", (char*)"clientUsername", (char*)"driverUsername",
                        (char*)"address", (char*)"destination", (char*)"passengers", (char*)"minutes",(char*)"amount"};
    char stringData[sizeof(messages) / sizeof(char*) - 6][BUFFER_SIZE];
    short status;
    for(int i = 0, j = 0; i < sizeof(messages) / sizeof(char*); i++) {
        if(inp.eof()) {
            throw std::runtime_error("Row consists of incomplete data!");
        }
        switch(i) {
            case 1:
                inp >> status;
                inp.ignore(1, ',');
                break;
            case 4:
                inp >> address;
//                    inp.ignore(1, ','); - no need to clear a comma, as it is handled by Location
                break;
            case 5:
                inp >> destination;
//                    inp.ignore(1, ','); - no need to clear a comma, as it is handled by Location
                break;
            case 6:
                inp >> passengers;
                inp.ignore(1, ',');
                break;
            case 7:
                inp >> minutes;
                inp.ignore(1, ',');
                break;
            case 8:
                inp >> amount;
                inp.ignore(1, ',');
                break;
            default:
                inp.getline(stringData[j++], BUFFER_SIZE, ',');
        }
    }
    if(!inp.eof()) {
        throw std::runtime_error("Row consists of too much data!");
    }
    if(strcmp(stringData[2], "NULL") == 0) {
        driver = nullptr;
    }
    for(int k = 0; k < users.getSize(); k++) {
        if(strcmp(users[k]->getUsername().c_str(), stringData[1]) == 0) {
            setClient(dynamic_cast<Client*>(&*users[k])); // it is desired to be nullptr, if for some reason a user is of wrong kind
        }
        else if(strcmp(stringData[2], "NULL") != 0 && strcmp(users[k]->getUsername().c_str(), stringData[2]) == 0) {
            setDriver(dynamic_cast<Driver*>(&*users[k])); // it is desired to be nullptr, if for some reason a user is of wrong kind
        }
    }
    setID(stringData[0]);
    setStatus((OrderStatus)status);
    return inp;
}

std::ostream& Order::write(std::ostream& out) const {
    out << getID() << ',';
    out << (int)getStatus() << ',';
    out << getClient()->getUsername() << ',';
    if(getDriver()) {
        out << getDriver()->getUsername() << ',';
    }
    else {
        out << "NULL" << ',';
    }
    out << getAddress().getName() << " " << getAddress().getPoint().x << " " << getAddress().getPoint().y <<  ',';
    out << getDestination().getName() << " " << getDestination().getPoint().x << " " << getDestination().getPoint().y <<  ',';
    out << getPassengers() << ',';
    out << getMinutes() << ',';
    out << getAmount();
    return out;
}