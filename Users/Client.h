#include "User.h"

class Client: public User {
    size_t wallet = 0;

public:
    Client() = default;
    Client(const char* username, const char* password, const char* firstName, const char* lastName): User(username, password, firstName, lastName) {}
    Client(const Client& other) = default;
    Client(Client&& other) = default;
    ~Client() override = default;

    size_t getBalance() const;
    double getBalanceInLeva() const;
    void setAmount(size_t amount);
    void setAmountInLeva(double amount);

    void depositAmount(double leva);
    void withdrawAmount(double leva);
    UserType getType() const override;

};