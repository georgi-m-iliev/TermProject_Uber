#include "User.h"
#include "../Utilities/Location.h"
#include "../Utilities/PhoneNumber.h"
#include "../Utilities/MyString.h"

class Driver: User {
    MyString carNumber;
    PhoneNumber phone;
    Location currentLocation;
    double rating = 0;
public:
    Driver() = default;
    Driver(const char* username, const char* password, const char* firstName, const char* lastName,
            const char* carNumber, const char* phone): User(username, password, firstName, lastName) {}
    Driver(const Driver& other) = default;
    Driver(Driver&& other) = default;
    ~Driver() override = default;


    UserType getType() const override;

    friend class Order;
};