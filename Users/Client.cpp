#include "Client.h"

Client* Client::clone() const {
    return new Client(*this);
}

UserType Client::getType() const {
    return UserType::Client;
}
