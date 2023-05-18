#pragma once
#include "User.h"

class Client: public User {
public:
    Client() = default;
    Client(const char* username, const char* password, const char* firstName, const char* lastName): User(username, password, firstName, lastName) {}
    Client(const Client& other) = default;
    Client(Client&& other) = default;
    ~Client() override = default;
    Client* clone() const override;

public:

    UserType getType() const override;

};