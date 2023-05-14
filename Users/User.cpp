//
// Created by georgi on 4.5.2023 г..
//

#include "User.h"
#include "../Security/SHA256.h"
#include <cstring>

User::User(const char* username, const char* password, const char* firstName, const char* lastName) :
        username(username), passwordHash(SHA256::calculate(password)),
        firstName(firstName), lastName(lastName) {}

const MyString &User::getUsername() const {
    return username;
}

const MyString& User::getFirstName() const {
    return firstName;
}

const MyString& User::getLastName() const {
    return lastName;
}

bool User::verifyPassword(const char* password) const {
    return strcmp(SHA256::calculate(password), passwordHash.c_str()) == 0;
}

void User::setUsername(const char* username) {
    this->username = username;
}

void User::setPassword(const char* password) {
    this->passwordHash = SHA256::calculate(password);
}

void User::setFirstName(const char* name) {
    this->firstName = name;
}

void User::setLastName(const char* name) {
    this->lastName = name;
}
