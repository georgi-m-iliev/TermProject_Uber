#pragma once
#include "../Utilities/Order.h"

class OrderCollection {
    Order** orders;
    size_t size;
    size_t capacity;

    void copyFrom(const OrderCollection& other);
    void moveFrom(OrderCollection&& other);
    void free();
    void resize();

public:
    OrderCollection(): OrderCollection(0) {}
    explicit OrderCollection(size_t capacity);
    OrderCollection(const OrderCollection& other);
    OrderCollection(OrderCollection&& other) noexcept ;

    ~OrderCollection();

    OrderCollection& operator=(const OrderCollection& other);
    OrderCollection& operator=(OrderCollection&& other) noexcept;
    Order& operator[](int ind);
    const Order& operator[](int ind) const;
    Order& get(int ind);

    void add(const Order& order);
    void add(const char* addressName, int addressX, int addressY,
             const char* destinationName, int destinationX, int destinationY,
             short passengers);
    void add(const char* addressName, int addressX, int addressY, const char* addressNote,
             const char* destinationName, int destinationX, int destinationY, const char* destinationNote,
             short passengers);
    void add(Order&& order);
    size_t getSize() const;
    size_t getCapacity() const;
};