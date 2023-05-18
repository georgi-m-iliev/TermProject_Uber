#include "Driver.h"

Driver* Driver::clone() const {
    return new Driver(*this);
}

const char* Driver::getCarNumber() const {
    return this->carNumber.c_str();
}

const char* Driver::getPhoneNumber() const {
    return this->phone.c_str();
}

const Location& Driver::getCurrentLocation() const {
    return this->currentLocation;
}

double Driver::getRating() const {
    return this->rating;
}

void Driver::setCarNumber(const char* str) {
    this->carNumber = str;
}

void Driver::setPhoneNumber(const char* str) {
    this->phone = str;
}

void Driver::setLocation(const char* name, int x, int y) {
    this->currentLocation = {name, x, y};
}

void Driver::addRating(int rating) const {
    this->rating += rating;
    this->rating /= 2.0;
}

UserType Driver::getType() const {
    return UserType::Driver;
}

void Driver::setRating(double rating) {
    this->rating = rating;
}
