#pragma once
#include "MyString.h"

struct Point {
    int x;
    int y;
    Point(): x(0), y(0) {}
    Point(int x, int y): x(x), y(y) {}
};

class Location {
    MyString name;
    MyString note;
    Point point;

public:
    Location() = default;
    Location(const char* name, int x, int y): name(name), point(x, y) {}
    Location(const char* name, int x, int y, const char* note): name(name), point(x, y), note(note) {}

    const MyString& getName() const;
    const MyString& getNote() const;
    const Point& getPoint() const;

    void setName(const char* name);
    void setNote(const char* note);
    void setPoint(int x, int y);

    friend std::ostream& operator<<(std::ostream& os, const Location& loc);
    friend std::istream& operator>>(std::istream& is, Location& loc);
    friend double distanceBtwn(const Location& lhs, const Location& rhs);
};

std::ostream& operator<<(std::ostream& os, const Location& loc);
std::istream& operator>>(std::istream& is, Location& loc);
double distanceBtwn(const Location& lhs, const Location& rhs);
