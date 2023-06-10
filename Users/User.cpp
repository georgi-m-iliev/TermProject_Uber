#include "User.h"
#include "../Security/SHA256.h"

User::User(const char* username, const char* password, const char* firstName, const char* lastName, const size_t amount) :
        username(username), passwordHash(SHA256::calculate(password)),
        firstName(firstName), lastName(lastName), wallet(amount) {}

const MyString& User::getUsername() const {
    return username;
}

const MyString& User::getFirstName() const {
    return firstName;
}

const MyString& User::getLastName() const {
    return lastName;
}

const MyString& User::getPasswordHash() const {
    return passwordHash;
}

bool User::verifyPassword(const char* password) const {
    return SHA256::compare(password, passwordHash.c_str());
}

void User::setUsername(const char* username) {
    this->username = username;
}

void User::setPasswordHash(const char* password) {
    this->passwordHash = password;
}

void User::setPassword(const char* password) {
    if(password == nullptr) {
        throw std::invalid_argument("Invalid data received for field password!");
    }
    this->passwordHash = SHA256::calculate(password);
}

void User::setFirstName(const char* name) {
    firstName = name;
}

void User::setLastName(const char* name) {
    lastName = name;
}

double User::getBalance() const {
    return (double)wallet / 100.0;
}

size_t User::getBalanceNom() const {
    return wallet;
}

void User::displaySystemWarnings(std::ostream& os) {
    for(size_t i = 0; i < systemWarnings.getSize(); i++) {
        os << systemWarnings[i] << std::endl;
    }
    systemWarnings.clear();
}


void User::setBalance(double amount) {
    wallet = (size_t)(amount / 100.0);
}

void User::setBalanceNom(size_t amount) {
    wallet = amount;
}

void User::addSystemWarning(MyString message) {
    systemWarnings.push_back(std::move(message));
}

void User::addSystemWarning(const WarningType warning, MyString id) {
    switch(warning) {
        case WarningType::NEW_ORDER:
            if(getType() != UserType::Driver) {
                throw std::logic_error("Can't add this type of message to Driver!");
            }
            systemWarnings.push_back("New order for you with id: " + id);
        break;
        case WarningType::ORDER_ACCEPTED:
            if(getType() != UserType::Client) {
                throw std::logic_error("Can't add this type of message to Client!");
            }
            systemWarnings.push_back("Your order with id: " + id + " has been accepted!");
        break;
        case WarningType::ORDER_CANCELD:
            if(getType() != UserType::Driver) {
                throw std::logic_error("Can't add this type of message to Driver!");
            }
            systemWarnings.push_back("Your order with id: " + id + " has been canceled!");
        break;
    }
}

void User::depositAmount(double amount) {
    wallet += (size_t)(amount * 100);
}

void User::withdrawAmount(double amount) {
    wallet -= (size_t)(amount * 100);
}

std::ostream& operator<<(std::ostream& os, const User& user) {
    std::cout << "User: "  << user.getUsername() << std::endl << user.getFirstName() << " " << user.getLastName() << std::endl;
    return os;
}
