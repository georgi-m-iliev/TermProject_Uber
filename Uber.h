#include "Users/User.h"
#include "Utilities/Order.h"
#include "Utilities/Location.h"

class Uber {
    Order** orders;
    static double netEarnings;


public:
    Uber() = default;


    void registerUser();
    void order();
    void checkOrder();
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