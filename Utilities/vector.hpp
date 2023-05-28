#pragma once
#include <iostream>

template <class T>
class vector {
    size_t size;
    size_t capacity;
    T* elements;

    void copyFrom(const vector<T>& other);
    void moveFrom(vector<T>&& other);
    void resize(size_t cap);
    void free();

public:
    vector<T>();
    explicit vector(size_t n);
    vector(size_t n, const T& elem);
    vector(const vector<T>& other);
    vector(vector<T>&& other) noexcept;
    ~vector();

    vector<T>& operator=(const vector<T>& other);
    vector<T>& operator=(vector<T>&& other) noexcept;

    void push_back(const T& item);
    void push_back(T&& item);
    void pop_back();
    T& operator[](size_t at);
    const T& operator[](size_t at) const;
    bool empty() const;
    size_t getSize() const;
    size_t getCapacity() const;
    void clear();
};

template<class T>
void vector<T>::copyFrom(const vector<T>& other) {
    capacity = other.capacity;
    size = other.size;
    elements = new T[capacity];
    for(int i = 0; i < size; i++) {
        elements[i] = other.elements[i];
    }
}

template<class T>
void vector<T>::moveFrom(vector<T>&& other) {
    capacity = other.capacity;
    size = other.size;
    elements = other.elements;
    other.elements = nullptr;
}

template<class T>
void vector<T>::resize(size_t cap) {
    T* newArray = new T[cap];
    capacity = cap;
    for(int i = 0; i < size; i++) {
        newArray[i] = elements[i];
    }
    delete[] elements;
    elements = newArray;
}

template<class T>
void vector<T>::free() {
    delete[] elements;
}

template<class T>
vector<T>::vector() {
    size = 0;
    capacity = 0;
    elements = nullptr;
}

template<class T>
vector<T>::vector(size_t n) {
    size = n;
    capacity = n;
    elements = new T[n];
}

template<class T>
vector<T>::vector(size_t n, const T& elem) {
    size = n;
    capacity = n;
    elements = new T[n];
    for(int i = 0; i < n; i++ ) {
        elements[i] = elem;
    }
}

template<class T>
vector<T>::vector(const vector<T>& other): vector() {
    copyFrom(other);
}

template<class T>
vector<T>::vector(vector<T>&& other) noexcept : vector() {
    moveFrom(std::move(other));
}

template<class T>
vector<T>::~vector() {
    free();
}

template<class T>
vector<T>& vector<T>::operator=(const vector<T>& other) {
    if(this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

template<class T>
vector<T>& vector<T>::operator=(vector<T>&& other) noexcept {
    if(this != &other) {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

template<class T>
void vector<T>::push_back(const T& item) {
    if(size == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    elements[size++] = item;
}

template<class T>
void vector<T>::push_back(T&& item) {
    if(size == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    elements[size++] = std::move(item);
}

template<class T>
void vector<T>::pop_back() {
    if(empty()) {
        throw std::runtime_error("Cannot pop from empty state!");
    }
    size--;
}

template<class T>
T& vector<T>::operator[](size_t at) {
    if(at >= size) {
        throw std::invalid_argument("Index out of bounds!");
    }
    return elements[at];
}

template<class T>
const T& vector<T>::operator[](size_t at) const {
    if(at >= size) {
        throw std::invalid_argument("Index out of bounds!");
    }
    return elements[at];
}

template<class T>
bool vector<T>::empty() const {
    return size == 0;
}

template<class T>
size_t vector<T>::getSize() const {
    return size;
}

template<class T>
size_t vector<T>::getCapacity() const {
    return capacity;
}

template<class T>
void vector<T>::clear() {
    size = 0;
}