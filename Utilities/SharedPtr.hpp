#pragma once
#include <iostream>

template<typename T>
class SharedPtr {
    T* data;
    unsigned* pointersCount;

    void free();
    void copyFrom(const SharedPtr<T>& other);
    void moveFrom(SharedPtr<T>&& other);

public:
    SharedPtr();
    SharedPtr(T* data);
    ~SharedPtr();
    SharedPtr(const SharedPtr<T>& other);
    SharedPtr(SharedPtr<T>&& other) noexcept;

    SharedPtr& operator=(const SharedPtr<T>& other);
    SharedPtr& operator=(SharedPtr<T>&& other) noexcept;
    T& operator*();
    const T& operator*() const;
    T* operator->();
    const T* operator->() const;
};

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept {
    if(this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) noexcept{
    moveFrom(std::move(other));
}

template<typename T>
void SharedPtr<T>::moveFrom(SharedPtr<T>&& other) {
    data = other.data;
    other.data = nullptr;
    pointersCount = other.pointersCount;
    other.pointersCount = nullptr;
}

template<typename T>
T* SharedPtr<T>::operator->() {
    return data;
}

template<typename T>
const T* SharedPtr<T>::operator->() const {
    return data;
}

template<typename T>
void SharedPtr<T>::free() {
    if(data == nullptr && pointersCount == nullptr) {
        return;
    }
    if(*pointersCount == 1) {
        delete data;
        delete pointersCount;
    }
    else {
        (*pointersCount)--;
    }
}

template<typename T>
void SharedPtr<T>::copyFrom(const SharedPtr<T>& other) {
    data = other.data;
    pointersCount = other.pointersCount;
    (*pointersCount)++;
}

template<typename T>
SharedPtr<T>::SharedPtr() {
    data = nullptr;
    pointersCount = nullptr;
}

template<typename T>
SharedPtr<T>::SharedPtr(T* data) {
    this->data = data;
    pointersCount = new unsigned(1);
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) {
    data = other.data;
    pointersCount = other.pointersCount;
    (*pointersCount)++;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
    if(this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
const T& SharedPtr<T>::operator*() const {
    if(data == nullptr) {
        throw std::runtime_error("Pointer not set");
    }
    return *data;
}

template<typename T>
T& SharedPtr<T>::operator*() {
    if(data == nullptr) {
        throw std::runtime_error("Pointer not set");
    }
    return *data;
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
    free();
}

//template<typename T>
//T* SharedPtr<T>::operator&() {
//    return data;
//}
//
//template<typename T>
//const T* SharedPtr<T>::operator&() const {
//    return data;
//}