#pragma once
#include "../Users/Client.h"
#include "../Users/Driver.h"

class UserCollection {
    User** users;
    size_t size;
    size_t capacity;

    void copyFrom(const UserCollection& other);
    void moveFrom(UserCollection&& other);
    void free();
    void resize();

public:
    UserCollection(): UserCollection(0) {}
    explicit UserCollection(size_t capacity);
    UserCollection(const UserCollection& other);
    UserCollection(UserCollection&& other) noexcept ;

    ~UserCollection();

    UserCollection& operator=(const UserCollection& other);
    UserCollection& operator=(UserCollection&& other) noexcept;
    User& operator[](int ind);
    const User& operator[](int ind) const;
    User& get(int ind);

    void add(const User& user);
    void move(const User&& user);
    void add(const char* username, const char* password, const char* firstName, const char* lastName);
    void add(const char* username, const char* password, const char* firstName, const char* lastName,
             const char* carNumber, const char* phone);
    size_t getSize() const;
    size_t getCapacity() const;
};