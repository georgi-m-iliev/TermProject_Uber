#include "Client.h"

namespace {
    const int BUFFER_SIZE = 512;
}

Client::Client(const char* username, const char* password,
               const char* firstName, const char* lastName) : User(username, password, firstName, lastName, 0) {}

Client::Client(const char* username, const char* password,
               const char* firstName, const char* lastName, const size_t amount):
                    User(username, password, firstName, lastName, amount) {}

Client* Client::clone() const {
    return new Client(*this);
}

UserType Client::getType() const {
    return UserType::Client;
}

std::istream& Client::read(std::istream& inp) {
    [[maybe_unused]] static char* messages[] = {
            (char*)"username", (char*)"password",(char*)"firstName", (char*)"lastName", (char*)"amount"
    };
    char buffer2[sizeof(messages) / sizeof(char*) - 1][BUFFER_SIZE];
    size_t amount;
    for(int i = 0; i < sizeof(messages) / sizeof(char*); i++) {
        if(inp.eof()) {
            throw std::runtime_error("Row consists of incomplete data!");
        }
        switch(i) {
            case 4:
                inp >> amount;
                break;
            default:
                inp.getline(buffer2[i], BUFFER_SIZE, ',');
        }
    }
    if(!inp.eof()) {
        throw std::runtime_error("Row consists of too much data!");
    }
    setUsername(buffer2[0]);
    setPasswordHash(buffer2[1]);
    setFirstName(buffer2[2]);
    setLastName(buffer2[3]);
    setBalanceNom(amount);
    return inp;
}

std::ostream& Client::write(std::ostream& out) const {
    out << (int)getType() << ',';
    out << getUsername() << ',';
    out << getPasswordHash() << ',';
    out << getFirstName() << ',';
    out << getLastName() << ',';
    out << getBalanceNom();
    return out;
}
