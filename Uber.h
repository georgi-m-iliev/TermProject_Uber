#pragma once
#include "Utilities/vector.hpp"
#include "Utilities/SharedPtr.hpp"
#include "Users/Client.h"
#include "Users/Driver.h"
#include "Utilities/Order.h"

class Uber {
    vector<SharedPtr<User>> users;
    vector<SharedPtr<Order>> activeOrders;
    vector<SharedPtr<Order>> finishedOrders;

    User* activeUser;

    static double netEarnings;

    void load();
    void save();
    void checkUserLoggedIn(const char* message = nullptr) const;
    void checkActiveUserType(const UserType type) const;
    bool checkUserExist(const char* username) const;

    void readUsers(const char* filepath);
    void readOrders(const char* filepath, vector<SharedPtr<Order>>& col);

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
    void cancelOrder(const char* id);
    void payOrder(const char* id, double levas);
    void rateOrder(const char* id, short rating);
    void addMoney(double levas);

    void changeAddress();
    void checkMessages();
    void acceptOrder();
    void declineOrder();
    void finishOrder();
    void acceptPayment();
};