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
    static MyString path;

    void readUsers(const char* filepath);
    void readOrders(const char* filepath, vector<SharedPtr<Order>>& col, bool addNet);
    void saveUsers(const char* filepath);
    void saveOrders(const char* filepath, vector<SharedPtr<Order>>& col);
    void load();
    void save();

    void checkUserLoggedIn(const char* message = nullptr) const;
    void checkActiveUserType(UserType type) const;
    bool checkUserExist(const char* username) const;
    Order& findOrder(const char* id);
    void moveOrderToFinished(const char* id);

    void handoutOrders();
public:
    Uber();
    Uber(const char* _path);
    ~Uber();

    void print();

    void registerUser(UserType type, std::stringstream& ss);
    void loginUser(std::stringstream& ss);
    void logoutUser();
    void changePassword(const char* password);

    void whoami() const;
    void order();
    void checkOrder(const char* id);
    void cancelOrder(const char* id);
    void payOrder(const char* id, double levas);
    void rateOrder(const char* id, short rating);
    void addMoney(double levas);

    void changeAddress(std::stringstream& ss);
    void checkMessages();
    void acceptOrder(const char* id, short minutes, double amount);
    void declineOrder(const char* id);
    void pickupPassenger(const char* id);
    void finishOrder(const char* id);
    void acceptPayment(const char* id, double amount);
};