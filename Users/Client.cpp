#include "Client.h"

Client::Client(const char* username, const char* password,
               const char* firstName, const char* lastName) : User(username, password, firstName, lastName) {}

Client* Client::clone() const {
    return new Client(*this);
}

UserType Client::getType() const {
    return UserType::Client;
}
