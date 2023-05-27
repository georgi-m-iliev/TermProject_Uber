// TODO: finish validation in constructor and operator >>
#include "PhoneNumber.h"

#include <cstring>

PhoneNumber::PhoneNumber(): data{} {
    data[0] = '\0';
}

PhoneNumber::PhoneNumber(const MyString &number): PhoneNumber(number.c_str()) {}

PhoneNumber::PhoneNumber(const char* text): data{} {
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



const char* PhoneNumber::c_str() const {
    return data;
}

std::istream& operator>>(std::istream& is, PhoneNumber& number) {
    is.getline(number.data, PhoneNumber::MAX_LENGTH);
    return is;
}

std::ostream& operator<<(std::ostream& os, const PhoneNumber& number) {
    os << number.data;
    return os;
}
