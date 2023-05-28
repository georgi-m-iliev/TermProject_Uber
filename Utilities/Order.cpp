#include <cstring>
#include "Order.h"
#include <chrono>

namespace {
    int absInt(const int num) {
        return num < 0 ? -num : num;
    }

    void numToStr(size_t num, char* str) {
        int len = 0;
        size_t copy = num;
        do {
            copy /= 10;
            len++;
        } while(copy != 0);
        for(int i = len - 1; i >= 0; i--) {
            str[i] = (char)(num % 10 + '0');
            num /= 10;
        }
        str[len] = '\0';
    }
}

void Order::calcID() {
    static size_t EPOCH_START = 1684108800;
    char str[20];
    size_t seconds = std::chrono::system_clock::now().time_since_epoch() / std::chrono::seconds(1);
    seconds -= EPOCH_START;
    numToStr(seconds, str);
// 212413
    for(int i = 0; i < strlen(str); i++) {
        if(i % 2 == 0) {
            str[i] += 'A' - '0';
        }
        else if(i % 3 == 0) {
            str[i] -= 8;
            str[i] += absInt(address.getPoint().x - address.getPoint().y);
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
             const Location& address, const Location& destination, const short passengers, const size_t amount) {
    this->id = id;
    this->status = status;
    this->client = client;
    this->driver = driver;
    this->address = address;
    this->destination = destination;
    this->passengers = passengers;
    this->amount = amount;
    this->minutes = -1;
}

const char* Order::getID() const {
    return id.c_str();
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

size_t Order::getAmount() const {
    return amount;
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
}

void Order::setDestination(const char* name, int x, int y, const char* note) {
    destination.setName(name);
    destination.setPoint(x, y);
    if(strlen(note) != 0) {
        destination.setNote(note);
    }
}

void Order::setPassengers(short passengers) {
    this->passengers = passengers;
    calcID();
}

void Order::setMinutes(short minutes) {
    this->minutes = minutes;
}

void Order::setAmount(size_t amount) {
    this->amount = amount;
}

void Order::rateDriver(short rating) {
    if(this->driver == nullptr) {
        //TODO: add path
        return;
    }
    driver->addRating(rating);
}

std::ostream& operator<<(std::ostream& os, const Order& order) {
    std::cout << std::endl << "---------------====================---------------" << std::endl;
    std::cout << "Order ID: " << order.getID() << std::endl;
    std::cout << "[ " << order.getAddress() << " ] -> [ " << order.getDestination() << " ]" << std::endl;
    std::cout << "Passengers: " << order.getPassengers() << "  Amount: " ;
    if(order.getAmount() == 0) {
        std::cout << "NaN";
    }
    else {
        std::cout << order.getAmount() << " ";
    }
    std::cout << "Waiting time: ";
    if(order.getMinutes() == -1) {
        std::cout << "NaN";
    }
    else {
        std::cout << order.getMinutes();
    }
    std::cout << " minutes" << std::endl << std::endl;
    return os;
}

double Order::getAmountInLeva() const {
    return (double)amount / 100.0;
}