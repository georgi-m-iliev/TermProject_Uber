#include "Client.h"

Client::Client(const char* username, const char* password,
               const char* firstName, const char* lastName) : User(username, password, firstName, lastName, 0) {}

Client::Client(const char* username, const char* password,
               const char* firstName, const char* lastName, const size_t amount):
                    User(username, password, firstName, lastName, amount) {}

Client* Client::clone() const {
    return new Client(*this);
}

UserType Client::getType() const {
    return UserType::Client;
}
