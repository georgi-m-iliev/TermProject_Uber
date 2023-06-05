#include "Driver.h"

Driver::Driver(const char* username, const char* password, const char* firstName, const char* lastName,
               const char* carNumber, const char* phone):
        User(username, password, firstName, lastName, 0),
        carNumber(carNumber), phone(phone), currentLocation{}, rating(0), availability(true) {}

Driver::Driver(const char* username, const char* password, const char* firstName, const char* lastName,
               const size_t amount, const char* carNumber, const char* phone, const double rating, const bool availability):
                    User(username, password, firstName, lastName, amount),
                    carNumber(carNumber), phone(phone), currentLocation{}, rating(rating), availability(availability) {}
Driver* Driver::clone() const {
    return new Driver(*this);
}

const char* Driver::getCarNumber() const {
    return carNumber.c_str();
}

const char* Driver::getPhoneNumber() const {
    return phone.c_str();
}

const Location& Driver::getCurrentLocation() const {
    return currentLocation;
}

double Driver::getRating() const {
    return rating;
}

bool Driver::isAvailable() const {
    return availability;
}

void Driver::setCarNumber(const char* str) {
    carNumber = str;
}

void Driver::setPhoneNumber(const char* str) {
    phone = str;
}

void Driver::setCurrentLocation(const char* name, int x, int y) {
    currentLocation = {name, x, y};
}


void Driver::setCurrentLocation(const Location& loc) {
    currentLocation = loc;
}

void Driver::setRating(double rating) {
    this->rating = rating;
}

void Driver::addRating(int rating) {
    this->rating += rating;
    this->rating /= 2.0;
}

UserType Driver::getType() const {
    return UserType::Driver;
}

void Driver::setAvailability(bool status) {
    availability = status;
}
