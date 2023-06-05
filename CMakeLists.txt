cmake_minimum_required(VERSION 3.18)
project(OOP_TermProject_Uber)

set(CMAKE_CXX_STANDARD 17)

add_executable(OOP_TermProject_Uber main.cpp Security/SHA256.cpp Security/SHA256.h Utilities/MyString.cpp Utilities/MyString.h Users/User.cpp Users/User.h Utilities/Order.cpp Utilities/Order.h Utilities/Location.cpp Utilities/Location.h Uber.cpp Uber.h Users/Client.cpp Users/Client.h Users/Driver.cpp Users/Driver.h Utilities/PhoneNumber.cpp Utilities/PhoneNumber.h Utilities/ObjPtr.hpp Utilities/vector.hpp)