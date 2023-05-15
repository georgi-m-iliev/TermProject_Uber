//
// Created by georgi on 4.5.2023 г..
//

#include "Order.h"

void Order::calcID() {

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
}

Order::Order(const char* addressName, int addressX, int addressY, const char* addressNote, const char* destinationName,
             int destinationX, int destinationY, const char* destinationNote, short passengers): Order() {
    this->status = OrderStatus::CREATED;
}

uint64_t Order::getID() const {
    return 0;
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

const Location &Order::getAddress() const {
    return this->address;
}

const Location &Order::getDestination() const {
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
    if(note != nullptr) {
        this->address.setNote(note);
    }
}

void Order::setDestination(const char* name, int x, int y, const char* note) {
    this->destination.setName(name);
    this->destination.setPoint(x, y);
    if(note != nullptr) {
        this->destination.setNote(note);
    }
}

void Order::setPassengers(short passengers) {
    this->passengers = passengers;
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
