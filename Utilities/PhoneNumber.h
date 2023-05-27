#pragma once
#include "MyString.h"

struct PhoneNumber {
    static const int MAX_LENGTH = 20;
    char data[MAX_LENGTH];

public:
    PhoneNumber();
    PhoneNumber(const MyString& number);
    PhoneNumber(const char text[10]);

    const char* c_str() const;
    friend std::istream& operator>>(std::istream& is, PhoneNumber& number);
    friend std::ostream& operator<<(std::ostream& os, const PhoneNumber& number);

};

std::istream& operator>>(std::istream& is, PhoneNumber& number);
std::ostream& operator<<(std::ostream& os, const PhoneNumber& number);
