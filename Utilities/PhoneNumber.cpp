#include "PhoneNumber.h"
#include <cstring>

void PhoneNumber::validateAndSave(const char* text) {
    int length = (int)strlen(text);
    if(length + 1 > MAX_LENGTH) {
        throw std::invalid_argument("Phone number too long!");
    }
    int j = 0;
    for(int i = 0; i < length; i++) {
        if(text[i] < '0' || text[i] > '9') {
            if(i == 0 && text[i] == '+') {

            }
            else {
                break;
            }
        }
        data[j++] = text[i];
    }
    data[j] = '\0';
}

PhoneNumber::PhoneNumber(): data{} {
    data[0] = '\0';
}

PhoneNumber::PhoneNumber(const MyString &number): PhoneNumber(number.c_str()) {}

PhoneNumber::PhoneNumber(const char* text): data{} {
    validateAndSave(text);
}



const char* PhoneNumber::c_str() const {
    return data;
}

std::istream& operator>>(std::istream& is, PhoneNumber& number) {
    char buffer[PhoneNumber::MAX_LENGTH];
    is.getline(buffer, PhoneNumber::MAX_LENGTH);
    number.validateAndSave(buffer);
    return is;
}

std::ostream& operator<<(std::ostream& os, const PhoneNumber& number) {
    os << number.data;
    return os;
}
