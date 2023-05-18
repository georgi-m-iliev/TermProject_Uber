//
// Created by georgi on 4.5.2023 г..
//

#include <cstring>
#include "Order.h"
#include <chrono>

namespace {
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

// izvadi 8 ot neshtoto i dobavi broi putnici
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
            str[i] += this->passengers;
        }
        else {
            str[i] += 'a' - '0';
        }
    }

    this->id = str;
}

Order::Order() {
    this->status = OrderStatus::EMPTY;
    this->client = nullptr;
    this->driver = nullptr;
    this->passengers = 0;
    this->amount = 0;
}

Order::Order(const char* addressName, int addressX, int addressY, const char* destinationName, int destinationX,
             int destinationY, short passengers): Order() {
    this->status = OrderStatus::CREATED;
    calcID();
}

Order::Order(const char* addressName, int addressX, int addressY, const char* addressNote, const char* destinationName,
             int destinationX, int destinationY, const char* destinationNote, short passengers): Order() {
    this->status = OrderStatus::CREATED;
    calcID();
}

Order::Order(const char* id, const OrderStatus status, const Client* client, const Driver* driver,
             const Location& address, const Location& destination, const short passengers, const size_t amount) {
    this->id = id;
    this->status = status;
    this->client = client;
    this->driver = driver;
    this->address = address;
    this->destination = destination;
    this->passengers = passengers;
    this->amount = amount;
}

const char* Order::getID() const {
    return this->id.c_str();
}

OrderStatus Order::getStatus() const {
    return this->status;
}

const Client& Order::getClient() const {
    return *this->client;
}

const Driver& Order::getDriver() const {
    return *this->driver;
}

const Location& Order::getAddress() const {
    return this->address;
}

const Location& Order::getDestination() const {
    return this->destination;
}

short Order::getPassengers() const {
    return this->passengers;
}


size_t Order::getAmount() const {
    return this->amount;
}

void Order::setStatus(OrderStatus status) {
    this->status = status;
}

void Order::setClient(const Client* client) {
    this->client = client;
}

void Order::setDriver(const Driver* driver) {
    this->driver = driver;
}

void Order::setAddress(const char* name, int x, int y, const char* note) {
    this->address.setName(name);
    this->address.setPoint(x, y);
    if(strlen(note) != 0) {
        this->address.setNote(note);
    }
}

void Order::setDestination(const char* name, int x, int y, const char* note) {
    this->destination.setName(name);
    this->destination.setPoint(x, y);
    if(strlen(note) != 0) {
        this->destination.setNote(note);
    }
}

void Order::setPassengers(short passengers) {
    this->passengers = passengers;
    calcID();
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
    std::cout << "---------------====================---------------" << std::endl;
    std::cout << "Your order ID: " << order.getID() << std::endl;
    std::cout << "[ " << order.getAddress() << " ] -> [ " << order.getDestination() << " ]" << std::endl;
    std::cout << "Passengers: " << order.getPassengers() << "  Amount: " << order.getAmount() << std::endl << std::endl;
    return os;
}