#include "UserCollection.h"


void UserCollection::copyFrom(const UserCollection& other) {
    this->users = new User*[other.capacity];
    this->size = other.size;
    this->capacity = other.capacity;
    for(int i = 0; i < this->size; i++) {
        this->users[i] = other.users[i];
    }
}

void UserCollection::moveFrom(UserCollection&& other) {

}

void UserCollection::free() {
    for(int i = 0; i < size; i++) {
        delete users[i];
    }
    delete[] users;
}

void UserCollection::resize() {
    this->capacity = this->size * 2;
    User** newArray = new User*[this->capacity];
    for(int i = 0; i < size; i++) {
        newArray[i] = this->users[i];
    }
    delete[] users;
    this->users = newArray;
}

UserCollection::UserCollection(size_t capacity) {
    this->users = new User*[capacity];
    this->size = 0;
    this->capacity = capacity;
}

UserCollection::UserCollection(const UserCollection& other):UserCollection() {
    copyFrom(other);
}

UserCollection::UserCollection(UserCollection&& other) noexcept:UserCollection()  {
    moveFrom(std::move(other));
}

UserCollection::~UserCollection() {
    free();
}

UserCollection& UserCollection::operator=(const UserCollection& other) {
    if(this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

UserCollection& UserCollection::operator=(UserCollection&& other) noexcept {
    if(this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

void UserCollection::add(const User& user) {
    if(this->size == this->capacity) {
        resize();
    }
    switch(user.getType()) {
        case UserType::Driver:
            users[this->size++] = (User*)new Driver((const Driver&)user);
            break;
        case UserType::Client:
            users[this->size++] = (User*)new Client((const Client&)user);
            break;
        default:
            throw std::invalid_argument("Error! Invalid user object!");
        break;
    }
}
