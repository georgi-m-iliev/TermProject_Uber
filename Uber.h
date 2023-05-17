#pragma once
#include "Collections/UserCollection.h"
#include "Collections/OrderCollection.h"

class Uber {
    UserCollection users;
    OrderCollection activeOrders;
    OrderCollection finishedOrders;

    User* activeUser;

    static double netEarnings;

    void load();
    void save();
    void checkUserLoggedIn(const char* message = nullptr) const;
    void checkActiveUserType(const UserType type) const;
    bool checkUserExist(const char* username) const;

public:
    Uber();
    ~Uber();


    void registerUser(UserType type, std::stringstream& ss);
    void loginUser(std::stringstream& ss);
    void logoutUser();
    void whoami() const;

    void order();
    void print();
    void checkOrder(const char* id);
    void cancelOrder();
    void payOrder();
    void rateOrder();
    void addMoney();

    void changeAddress();
    void checkMessages();
    void acceptOrder();
    void declineOrder();
    void finishOrder();
    void acceptPayment();
};