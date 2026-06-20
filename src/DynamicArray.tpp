#pragma once

#include <algorithm>

#include "DynamicArray.hpp"


// Конструкторы и деструктор
template <class T>
DynamicArray<T>::DynamicArray() : data(nullptr), size(0) {}

template <class T>
DynamicArray<T>::DynamicArray(int count) : size(count) {
    if (this->size < 0) {
        throw IndexOutOfRange("DynamicArray error: negative size");
    }
    this->data = (size > 0) ? new T[size]() : nullptr;
}

template <class T>
DynamicArray<T>::DynamicArray(T* items, int count) : DynamicArray(count) {
    std::copy(items, items + count, this->data);
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray& other) : DynamicArray(other.size) {
    std::copy(other.data, other.data + size, this->data);
}

template <class T>
DynamicArray<T>::DynamicArray(DynamicArray&& other) noexcept : data(other.data), size(other.size) {
    other.data = nullptr;
    other.size = 0;
}

template <class T>
DynamicArray<T>::~DynamicArray() {
    delete[] this->data;
}

// Геттеры, сеттеры и resize
template <class T>
void DynamicArray<T>::Set(int index, T value) {
    if (index < 0 || index >= this->size) {
        throw IndexOutOfRange("Set error: negative index");
    }
    this->data[index] = value;
}

template <class T>
const T& DynamicArray<T>::Get(int index) const {
    if (index < 0 || index >= this->size) {
        throw IndexOutOfRange("Get error: negative index");
    }
    if (this->size == 0) {
        throw EmptyCollectionError("Get error: empty collection is given");
    }
    return this->data[index];
}

template <class T>
int DynamicArray<T>::GetSize() const {
    return this->size;
}

template <class T>
IEnumerator<T>* DynamicArray<T>::GetEnumerator() const {
    return new Enumerator(this);
}

template <class T>
void DynamicArray<T>::Resize(int new_size) {
    if (new_size < 0) {
        throw IndexOutOfRange("Resize error: negative new_size");
    }
    T* new_data = new T[new_size];
    const int elem_to_copy = (this->size < new_size) ? this->size : new_size;
    std::copy(this->data, this->data + elem_to_copy, new_data);
    delete[] this->data;
    this->data = new_data;
    this->size = new_size;
}

// Операторы
template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    if (this != &other) {
        this->size = other.size;

        if (this->data) {
            delete[] this->data;
        }
        this->data = new T[size]();

        std::copy(other.data, other.data + size, this->data);
    }
    return *this;
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T>&& other) noexcept {
    if (this != &other) {
        delete[] this->data;
        this->data = other.data;
        this->size = other.size;
        other.data = nullptr;
        other.size = 0;
    }
    return *this;
}

template <class T>
T& DynamicArray<T>::operator[](int index) {
    if (this->GetSize() < index || index < 0) {
        throw IndexOutOfRange("operator[] error: index out of range");
    }
    return this->data[index];
}

template <class T>
const T& DynamicArray<T>::operator[](int index) const {
    if (this->GetSize() < index || index < 0) {
        throw IndexOutOfRange("operator[] error: index out of range");
    }
    return this->data[index];
}
