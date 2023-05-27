#pragma once
#include "Location.h"
#include "MyString.h"
#include "../Users/Client.h"
#include "../Users/Driver.h"

enum class OrderStatus {
    EMPTY,
    CREATED,
    AWAITING_DRIVER,
    ACCEPTED_BY_DRIVER,
    PASSENGER_TAKEN,
    DESTINATION_REACHED,
    AWAITING_RATING,
    FINISHED,
    CANCELED
};

class Order {
    MyString id;
    OrderStatus status;
    const Client* client;
    const Driver* driver;
    Location address;
    Location destination;
    short passengers;
    size_t amount;

    void calcID();

public:
    Order();
    Order(const char* addressName, int addressX, int addressY,
          const char* destinationName, int destinationX, int destinationY,
          short passengers);
    Order(const char* addressName, int addressX, int addressY, const char* addressNote,
          const char* destinationName, int destinationX, int destinationY, const char* destinationNote,
          short passengers);
    Order(const char* id, OrderStatus status, const Client* client, const Driver* driver,
          const Location& address, const Location& destination, short passengers, size_t amount);

    const char* getID() const;
    OrderStatus getStatus() const;
    const Client& getClient() const;
    const Driver& getDriver() const;
    const Location& getAddress() const;
    const Location& getDestination() const;
    short getPassengers() const;
    size_t getAmount() const;

    void setStatus(OrderStatus status);
    void setClient(const Client* client);
    void setDriver(const Driver* driver);
    void setAddress(const char* name, int x, int y, const char* note = nullptr);
    void setDestination(const char* name, int x, int y, const char* note = nullptr);
    void setPassengers(short passengers);
    void setAmount(size_t amount);
    void rateDriver(short rating);

    friend class Uber;
    friend std::ostream& operator<<(std::ostream& os, const Order& order);
};

std::ostream& operator<<(std::ostream& os, const Order& order);