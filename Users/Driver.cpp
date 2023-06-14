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

std::istream& Driver::read(std::istream& inp) {
    [[maybe_unused]] static char* messages[] = {(char*)"username", (char*)"password",
                                                (char*)"firstName", (char*)"lastName", (char*)"amount",
                                                (char*)"carNumber", (char*)"phoneNumber", (char*)"rating", (char*)"availability"};
    char buffer2[sizeof(messages) / sizeof(char*) - 3][BUFFER_SIZE];
    size_t balance;
    for(int i = 0, j = 0; i < sizeof(messages) / sizeof(char*); i++) {
        if(inp.eof()) {
            throw std::runtime_error("Row consists of incomplete data!");
        }
        switch(i) {
            case 4:
                inp >> balance;
                inp.ignore(1, ',');
                break;
            case 7:
                inp >> rating;
                inp.ignore(1, ',');
                break;
            case 8:
                inp >> availability;
            default:
                inp.getline(buffer2[j++], BUFFER_SIZE, ',');
        }
    }
    if(!inp.eof()) {
        throw std::runtime_error("Row consists of too much data!");
    }
    setUsername(buffer2[0]);
    setPasswordHash(buffer2[1]);
    setFirstName(buffer2[2]);
    setLastName(buffer2[3]);
    setBalance(balance);
    setCarNumber(buffer2[4]);
    setPhoneNumber(buffer2[5]);
    setRating(rating);
    return inp;
}

std::ostream& Driver::write(std::ostream& out) const {
    out << (int)getType() << ',';
    out << getUsername() << ',';
    out << getPasswordHash() << ',';
    out << getFirstName() << ',';
    out << getLastName() << ',';
    out << getBalanceNom();
    out << ',';
    out << getCarNumber() << ',';
    out << getPhoneNumber() << ',';
    out << getRating();
    out << isAvailable();
    return out;
}
