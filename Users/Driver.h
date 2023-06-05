#pragma once
#include "User.h"
#include "../Utilities/PhoneNumber.h"
#include "../Utilities/Location.h"

class Driver: public User {
    MyString carNumber;
    PhoneNumber phone;
    Location currentLocation;
    double rating;
    bool availability;
public:
    Driver() = default;

    Driver(const char* username, const char* password, const char* firstName, const char* lastName,
           const char* carNumber, const char* phone);
    Driver(const char* username, const char* password, const char* firstName, const char* lastName,
           size_t amount, const char* carNumber, const char* phone, double rating, bool availability);
    Driver(const Driver& other) = default;
    Driver(Driver&& other) = default;
    ~Driver() override = default;

    virtual Driver* clone() const override;

    const char* getCarNumber() const;
    const char* getPhoneNumber() const;
    const Location& getCurrentLocation() const;
    double getRating() const;
    bool isAvailable() const;

    void setCarNumber(const char* str);
    void setPhoneNumber(const char* str);
    void setCurrentLocation(const char* name, int x, int y);
    void setCurrentLocation(const Location& loc);
    void addRating(int rating);
    void setRating(double rating);
    void setAvailability(bool status);

    UserType getType() const override;
};