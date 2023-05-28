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
            const char* carNumber, const char* phone);
    Driver(const Driver& other) = default;
    Driver(Driver&& other) = default;
    ~Driver() override = default;

    virtual Driver* clone() const override;

    const char* getCarNumber() const;
    const char* getPhoneNumber() const;
    const Location& getCurrentLocation() const;
    double getRating() const;

    void setCarNumber(const char* str);
    void setPhoneNumber(const char* str);
    void setCurrentLocation(const char* name, int x, int y);
    void setCurrentLocation(const Location& loc);
    void addRating(int rating) const;
    void setRating(double rating);

    UserType getType() const override;
};