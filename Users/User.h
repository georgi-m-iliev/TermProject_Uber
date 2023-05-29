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
    size_t wallet = 0;

public:
    User() = default;
    User(const char* username, const char* password, const char* firstName, const char* lastName);
    User(const User& other) = default;
    User(User&& other) = default;
    virtual ~User() = default;
    
    virtual User* clone() const = 0;

    const MyString& getUsername() const;
    const MyString& getFirstName() const;
    const MyString& getLastName() const;
    const MyString& getPasswordHash() const;
    bool verifyPassword(const char* password) const;
    void setUsername(const char* username);
    void setPassword(const char* password);
    void setPasswordHash(const char* password);
    void setFirstName(const char* name);
    void setLastName(const char* name);


    size_t getBalance() const;
    double getBalanceInLeva() const;
    void setBalance(size_t amount);
    void setBalanceInLeva(double amount);
    void depositAmount(double leva);
    void withdrawAmount(double leva);

    virtual UserType getType() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const User& user);
};

std::ostream& operator<<(std::ostream& os, const User& user);