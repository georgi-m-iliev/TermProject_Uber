//
// Created by georgi on 4.5.2023 г..
//

#include "Location.h"

const MyString& Location::getName() const {
    return name;
}

const MyString& Location::getNote() const {
    return note;
}

const Point& Location::getPoint() const {
    return point;
}

void Location::setName(const char* name) {
    this->name = name;
}

void Location::setNote(const char* note) {
    this->note = note;

}

void Location::setPoint(int x, int y) {
    this->point = {x, y};
}

std::ostream& operator<<(std::ostream& os, const Location& loc) {
    os << loc.getName() << ": {" << loc.getPoint().x << ", " << loc.getPoint().y << "} ";
    os << "(" << loc.getNote() << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Location& loc) {
    char buffer[100];
    is.getline(buffer, 100, ' ');
    loc.setName(buffer);
    int x, y;
    is >> x >> y;
    loc.setPoint(x, y);
    is.getline(buffer, 100);
    loc.setNote(buffer);
    return is;
}