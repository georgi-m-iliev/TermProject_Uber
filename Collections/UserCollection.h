#pragma once
#include "../Users/User.h"
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
    UserCollection(size_t capacity);
    UserCollection(const UserCollection& other);
    UserCollection(UserCollection&& other) noexcept ;

    ~UserCollection();

    UserCollection& operator=(const UserCollection& other);
    UserCollection& operator=(UserCollection&& other) noexcept;


    void add(const User& user);




};