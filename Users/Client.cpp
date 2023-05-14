//
// Created by georgi on 8.5.2023 г..
//

#include "Client.h"

size_t Client::getBalance() const {
    return this->wallet;
}

double Client::getBalanceInLeva() const {
    return this->wallet / 100.0;
}


void Client::setAmount(size_t amount) {
    this->wallet = amount;
}

void Client::setAmountInLeva(double amount) {
    this->wallet = amount / 100;
}


void Client::depositAmount(double leva) {
    this->wallet += leva * 100;
}

void Client::withdrawAmount(double leva) {
    this->wallet -= leva / 100;
}

UserType Client::getType() const {
    return UserType::Client;
}
