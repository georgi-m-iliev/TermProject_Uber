#pragma once

#include <iostream>

template <typename T>
class ObjPtr {
    T* data;

    void free();
    void copyFrom(const ObjPtr<T>& other);
    void moveFrom(ObjPtr<T>&& other);

public:
    ObjPtr();
    ObjPtr(T* data);
    ~ObjPtr();
    ObjPtr(const ObjPtr<T>& other);
    ObjPtr(ObjPtr<T>&& other) noexcept;

    ObjPtr<T>& operator=(const ObjPtr<T>& other);
    ObjPtr<T>& operator=(ObjPtr<T>&& other) noexcept;
    T& operator*();
    const T& operator*() const;
    T* operator->();
    const T* operator->() const;
};

template <typename T>
void ObjPtr<T>::free() {
    delete data;
}

template <typename T>
void ObjPtr<T>::copyFrom(const ObjPtr<T>& other) {
    data = other.data->clone();
}

template <typename T>
void ObjPtr<T>::moveFrom(ObjPtr<T>&& other) {
    data = other.data;
    other.data = nullptr;
}

template <typename T>
ObjPtr<T>::ObjPtr() {
    data = nullptr;
}

template <typename T>
ObjPtr<T>::ObjPtr(T* data) {
    this->data = data;
}

template <typename T>
ObjPtr<T>::~ObjPtr() {
    free();
}

template <typename T>
ObjPtr<T>::ObjPtr(const ObjPtr<T>& other) {
    copyFrom(other);
}

template <typename T>
ObjPtr<T>::ObjPtr(ObjPtr<T>&& other) noexcept {
    moveFrom(std::move(other));
}

template <typename T>
ObjPtr<T>& ObjPtr<T>::operator=(const ObjPtr<T>& other) {
    if(this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
ObjPtr<T>& ObjPtr<T>::operator=(ObjPtr<T>&& other) noexcept {
    if(this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template <typename T>
T& ObjPtr<T>::operator*() {
    if(data == nullptr) {
        throw std::runtime_error("Pointer not set");
    }
    return *data;
}

template <typename T>
const T& ObjPtr<T>::operator*() const {
    if(data == nullptr) {
        throw std::runtime_error("Pointer not set");
    }
    return *data;
}

template <typename T>
T* ObjPtr<T>::operator->() {
    return data;
}

template <typename T>
const T* ObjPtr<T>::operator->() const {
    return data;
}