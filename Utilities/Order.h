#pragma once
#include "Location.h"
#include "MyString.h"
#include "../Users/Client.h"
#include "../Users/Driver.h"
#include "vector.hpp"

enum class OrderStatus {
    EMPTY,
    CREATED,
    AWAITING_DRIVER,
    ACCEPTED_BY_DRIVER,
    PASSENGER_PICKEDUP,
    DESTINATION_REACHED,
    PAID,
    AWAITING_RATING,
    FINISHED,
    CANCELED
};

class Order {
    MyString id;
    OrderStatus status;
    Client* client;
    Driver* driver;
    Location address;
    Location destination;
    short passengers;
    short minutes;
    size_t amount;

    void calcID();

    vector<const User*> driversDeclined; // this would be a shallow copy, as I would need it only during runtime
                                        // since we aren't allowing users to delete account, there won't be a problem
public:
    Order();
    Order(const char* addressName, int addressX, int addressY,
          const char* destinationName, int destinationX, int destinationY,
          short passengers);
    Order(const char* addressName, int addressX, int addressY, const char* addressNote,
          const char* destinationName, int destinationX, int destinationY, const char* destinationNote,
          short passengers);
    Order(const char* id, OrderStatus status, Client* client, Driver* driver,
          const Location& address, const Location& destination, short passengers, short minutes, size_t amount);

    Order* clone() const;

    const char* getID() const;
    const MyString& getID(bool) const;
    OrderStatus getStatus() const;
    const Client* getClient() const;
    const Driver* getDriver() const;
    Client* getClient();
    Driver* getDriver();
    const Location& getAddress() const;
    const Location& getDestination() const;
    short getPassengers() const;
    short getMinutes() const;
    double getAmount() const;
    size_t getAmountNom() const;

    void setStatus(OrderStatus status);
    void setClient(Client* client);
    void setDriver(Driver* driver);
    void setAddress(const char* name, int x, int y, const char* note = nullptr);
    void setDestination(const char* name, int x, int y, const char* note = nullptr);
    void setPassengers(short passengers);
    void setMinutes(short minutes);
    void setAmount(double amount);
    void setAmountNom(size_t amount);

    void rateDriver(short rating);

    void addDriverDeclined(const User* user);
    bool hasDeclined(const User* user) const;
    void clearDriversDeclined();

//    friend class Uber;
    friend std::ostream& operator<<(std::ostream& os, const Order& order);
};

std::ostream& operator<<(std::ostream& os, const Order& order);