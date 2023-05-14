#pragma once
#include "MyString.h"

struct Point {
    int x;
    int y;
};

class Location {
    MyString name;
    MyString note;
    Point point;

public:
    Location() = default;
    Location(const char* name, int x, int y): name(name), point{x, y} {}
    Location(const char* name, int x, int y, const char* note): name(name), point{x, y}, note(note) {}

    const MyString& getName() const;
    const MyString& getNote() const;
    const Point& getPoint() const;

    void setName(const char* name);
    void setNote(const char* notes);
    void setPoint(int x, int y);



};