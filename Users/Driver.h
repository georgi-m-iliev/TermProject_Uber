#pragma once
#include "User.h"
#include "../Utilities/PhoneNumber.h"
#include "../Utilities/Location.h"


class Driver: public User {
    MyString carNumber;
    PhoneNumber phone;
    Location currentLocation;
    mutable double rating = 0;
public:
    Driver() = default;
    Driver(const char* username, const char* password, const char* firstName, const char* lastName,
            const char* carNumber, const char* phone):
                User(username, password, firstName, lastName),
                carNumber(carNumber), phone(phone), currentLocation{}, rating(0)
    {}
    Driver(const Driver& other) = default;
    Driver(Driver&& other) = default;
    ~Driver() override = default;

    const char* getCarNumber() const;
    const char* getPhoneNumber() const;
    const Location& getCurrentLocation() const;
    double getRating() const;

    void setCarNumber(const char* str);
    void setPhoneNumber(const char* str);
    void setLocation(const char* name, int x, int y);
    void addRating(int rating) const;


    UserType getType() const override;

    friend class Order;
};