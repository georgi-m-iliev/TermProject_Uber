#pragma once
#include "User.h"

class Client: public User {
public:
    Client() = default;
    Client(const char* username, const char* password, const char* firstName, const char* lastName);
    Client(const char* username, const char* password, const char* firstName, const char* lastName, size_t amount);
    Client(const Client& other) = default;
    Client(Client&& other) = default;
    ~Client() override = default;

    virtual Client* clone() const override;

    UserType getType() const override;
};