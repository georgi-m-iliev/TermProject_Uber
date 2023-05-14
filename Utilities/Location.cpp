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

void Location::setNote(const char* notes) {
    this->note = notes;

}

void Location::setPoint(int x, int y) {
    this->point = {x, y};
}