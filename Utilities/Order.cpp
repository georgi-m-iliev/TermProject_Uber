//
// Created by georgi on 4.5.2023 г..
//

#include "Order.h"

void Order::calcID() {

}



Order::Order() {
    status = OrderStatus::CREATED;
    client = nullptr;
    driver = nullptr;
    passengers = 0;
    amount = 0;
}

Order::Order(const char* addressName, int addressX, int addressY, const char* destinationName, int destinationX,
             int destinationY, short passengers): Order() {

}

Order::Order(const char* addressName, int addressX, int addressY, const char* addressNote, const char* destinationName,
             int destinationX, int destinationY, const char* destinationNote, short passengers): Order() {

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

uint64_t Order::getID() const {
    return 0;
}

void Order::setAddress(const char* name, int x, int y, const char* note) {
    address.setName(name);
    address.setPoint(x, y);
    if(note != nullptr) {
        address.setNote(note);
    }
}

void Order::setDestination(const char* name, int x, int y, const char* note) {
    destination.setName(name);
}

void Order::setPassengers(short passengers) {
    this->passengers = passengers;
}

void Order::rateDriver(short rating) {
    if(driver == nullptr) {
        //TODO: add path
        return;
    }
    driver->rating += rating;
    driver->rating /= 2.0;
}
