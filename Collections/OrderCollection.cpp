#include "OrderCollection.h"


void OrderCollection::copyFrom(const OrderCollection& other) {
    this->orders = new Order*[other.capacity];
    this->size = other.size;
    this->capacity = other.capacity;
    for(int i = 0; i < this->size; i++) {
        this->orders[i] = other.orders[i];
    }
}

void OrderCollection::moveFrom(OrderCollection&& other) {
    this->orders = other.orders;
    other.orders = nullptr;
    this->size = other.size;
    this->capacity = other.capacity;
}

void OrderCollection::free() {
    for(int i = 0; i < size; i++) {
        delete orders[i];
    }
    delete[] orders;
}

void OrderCollection::resize() {
    this->capacity = this->size * 2;
    Order** newArray = new Order*[this->capacity];
    for(int i = 0; i < size; i++) {
        newArray[i] = this->orders[i];
    }
    delete[] orders;
    this->orders = newArray;
}

OrderCollection::OrderCollection(const size_t capacity) {
    this->orders = new Order*[capacity];
    this->size = 0;
    this->capacity = capacity;
}

OrderCollection::OrderCollection(const OrderCollection& other):OrderCollection() {
    copyFrom(other);
}

OrderCollection::OrderCollection(OrderCollection&& other) noexcept:OrderCollection()  {
    moveFrom(std::move(other));
}

OrderCollection::~OrderCollection() {
    free();
}

OrderCollection& OrderCollection::operator=(const OrderCollection& other) {
    if(this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

OrderCollection& OrderCollection::operator=(OrderCollection&& other) noexcept {
    if(this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

void OrderCollection::add(const Order& order) {
    if(this->size == this->capacity) {
        resize();
    }
    this->orders[this->size++] = new Order(order);
}

void OrderCollection::move(Order&& order) {
    if(this->size == this->capacity) {
        resize();
    }
    this->orders[this->size++] = new Order(std::move(order));
}

Order& OrderCollection::operator[](const int ind) {
    if(ind < 0 || ind >= size) {
        throw std::invalid_argument("Index out of bounds!");
    }
    return *orders[ind];
}

const Order& OrderCollection::operator[](const int ind) const {
    if(ind < 0 || ind >= size) {
        throw std::invalid_argument("Index out of bounds!");
    }
    return *orders[ind];
}

Order& OrderCollection::get(const int ind) {
    if(ind < 0 || ind >= size) {
        throw std::invalid_argument("Index out of bounds!");
    }
    return *orders[ind];
}

size_t OrderCollection::getSize() const {
    return this->size;
}

size_t OrderCollection::getCapacity() const {
    return this->capacity;
}
