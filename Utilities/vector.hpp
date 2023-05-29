#pragma once
#include <iostream>

template <class T>
class vector {
    T* elements;
    size_t size;
    size_t capacity;

    void copyFrom(const vector<T>& other);
    void moveFrom(vector<T>&& other);
    void resize(size_t cap);
    void free();

public:
    vector();
    explicit vector(size_t n);
    vector(size_t n, const T& elem);
    vector(const vector<T>& other);
    vector(vector<T>&& other) noexcept;
    ~vector();

    vector<T>& operator=(const vector<T>& other);
    vector<T>& operator=(vector<T>&& other) noexcept;

    void push_back(const T& item);
    void push_back(T&& item);
    void push_at(const T& item, const size_t ind);
    void push_at(T&& item, const size_t ind);
    void pop_back();
    void pop_at(const size_t ind);
    T& operator[](size_t at);
    const T& operator[](size_t at) const;

    bool empty() const;
    size_t getSize() const;
    size_t getCapacity() const;
    void clear();
};

template <typename T>
void vector<T>::copyFrom(const vector<T>& other) {
    capacity = other.capacity;
    size = other.size;
    elements = new T[capacity];
    for(size_t i = 0; i < size; i++) {
        elements[i] = other.elements[i];
    }
}

template <typename T>
void vector<T>::moveFrom(vector<T>&& other) {
    capacity = other.capacity;
    size = other.size;
    elements = other.elements;

    other.elements = nullptr;
    other.capacity = other.size = 0;
}

template <typename T>
void vector<T>::resize(size_t cap) {
    T* newArray = new T[cap];
    capacity = cap;
    for(size_t i = 0; i < size; i++) {
        newArray[i] = elements[i];
    }
    delete[] elements;
    elements = newArray;
}

template <typename T>
void vector<T>::free() {
    delete[] elements;
    elements = nullptr;
    capacity = size = 0;
}

template <typename T>
vector<T>::vector() {
    size = capacity = 0;
    elements = nullptr;
}

template <typename T>
vector<T>::vector(size_t n) {
    size = n;
    capacity = n;
    elements = new T[n];
}

template <typename T>
vector<T>::vector(size_t n, const T& elem) {
    size = n;
    capacity = n;
    elements = new T[n];
    for(size_t i = 0; i < n; i++ ) {
        elements[i] = elem;
    }
}

template <typename T>
vector<T>::vector(const vector<T>& other): vector() {
    copyFrom(other);
}

template <typename T>
vector<T>::vector(vector<T>&& other) noexcept: vector() {
    moveFrom(std::move(other));
}

template <typename T>
vector<T>::~vector() {
    free();
}

template <typename T>
vector<T>& vector<T>::operator=(const vector<T>& other) {
    if(this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

template <typename T>
vector<T>& vector<T>::operator=(vector<T>&& other) noexcept {
    if(this != &other) {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

template <typename T>
void vector<T>::push_back(const T& item) {
    if(size == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    elements[size++] = item;
}

template <typename T>
void vector<T>::push_back(T&& item) {
    if(size == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    elements[size++] = std::move(item);
}

template <typename T>
void vector<T>::push_at(const T& item, const size_t ind) {
    if(size == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    for(size_t i = size; i > ind; i--) {
        elements[ind] = elements[ind - 1];
    }
    elements[ind] = item;
    size++;
}

template <typename T>
void vector<T>::push_at(T&& item, const size_t ind) {
    if(size == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    for(size_t i = size; i > ind; i--) {
        elements[ind] = elements[ind - 1];
    }
    elements[ind] = std::move(item);
    size++;
}

template <typename T>
void vector<T>::pop_back() {
    if(empty()) {
        throw std::runtime_error("Cannot pop from empty state!");
    }
    size--;
}

template <typename T>
void vector<T>::pop_at(const size_t ind) {
    if(ind >= size) {
        throw std::out_of_range("Index out of bounds!");
    }
    for(size_t i = ind; i < size - 1; i++) {
        elements[i] = elements[i + 1];
    }
    size--;
}

template <typename T>
T& vector<T>::operator[](size_t at) {
    if(at >= size) {
        throw std::out_of_range("Index out of bounds!");
    }
    return elements[at];
}

template <typename T>
const T& vector<T>::operator[](size_t at) const {
    if(at >= size) {
        throw std::out_of_range("Index out of bounds!");
    }
    return elements[at];
}

template <typename T>
bool vector<T>::empty() const {
    return size == 0;
}

template <typename T>
size_t vector<T>::getSize() const {
    return size;
}

template <typename T>
size_t vector<T>::getCapacity() const {
    return capacity;
}

template <typename T>
void vector<T>::clear() {
    size = 0;
}