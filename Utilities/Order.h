#pragma once
#include "Location.h"
#include "MyString.h"
#include "../Users/Client.h"
#include "../Users/Driver.h"
#include "../Utilities/OrderID.h"

enum class OrderStatus {
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
    OrderID id;
    OrderStatus status;
    Client* client;
    Driver* driver;
    Location address;
    Location destination;
    short passengers;
    double amount;

    void calcID();

public:
    Order();
    Order(const char* addressName, int addressX, int addressY,
          const char* destinationName, int destinationX, int destinationY,
          short passengers);
    Order(const char* addressName, int addressX, int addressY, const char* addressNote,
          const char* destinationName, int destinationX, int destinationY, const char* destinationNote,
          short passengers);

    const Location& getAddress() const;
    const Location& getDestination() const;
    short getPassengers() const;
    uint64_t getID() const;

    void setAddress(const char* name, int x, int y, const char* note = nullptr);
    void setDestination(const char* name, int x, int y, const char* note = nullptr);
    void setPassengers(short passengers);
    void rateDriver(short rating) ;

};