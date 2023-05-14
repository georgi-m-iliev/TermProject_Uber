#pragma once
#include "../Utilities/MyString.h"

enum class UserType {
    Client = 0,
    Driver = 1
};

class User {
    MyString username;
    MyString passwordHash;
    MyString firstName;
    MyString lastName;
public:
    User() = default;
    User(const char* username, const char* password, const char* firstName, const char* lastName);
    User(const User& other) = default;
    User(User&& other) = default;
    virtual ~User() = default;

    const MyString& getUsername() const;
    const MyString& getFirstName() const;
    const MyString& getLastName() const;
    bool verifyPassword(const char* password) const;
    void setUsername(const char* username);
    void setPassword(const char* password);
    void setFirstName(const char* name);
    void setLastName(const char* name);

    virtual UserType getType() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const User& user);
};
std::ostream& operator<<(std::ostream& os, const User& user);
