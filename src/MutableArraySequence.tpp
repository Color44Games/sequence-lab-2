#pragma once

#include "MutableArraySequence.hpp"

// Конструкторы и деструктор
template <class T>
MutableArraySequence<T>::MutableArraySequence() : ArraySequence<T>() {}

template <class T>
MutableArraySequence<T>::MutableArraySequence(int count) : ArraySequence<T>(count) {}

template <class T>
MutableArraySequence<T>::MutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}

template <class T>
MutableArraySequence<T>::MutableArraySequence(const ArraySequence<T>& other) : ArraySequence<T>(other) {}

template <class T>
MutableArraySequence<T>::MutableArraySequence(const MutableArraySequence<T>& other) : ArraySequence<T>(other) {}

template <class T>
MutableArraySequence<T>::~MutableArraySequence() {}

// Операторы
template <class T>
MutableArraySequence<T>& MutableArraySequence<T>::operator=(const MutableArraySequence<T>& other) {
    if (this != &other) {
        this->size = other.size;
        this->data = other.data;
    }
    return *this;
}

template <class T>
T& MutableArraySequence<T>::operator[](int index) {
    if (index < 0 || index >= this->GetLength()) {
        throw IndexOutOfRange("operator[] error: index out of range");
    }
    return this->data[index];
}

template <class T>
const T& MutableArraySequence<T>::operator[](int index) const {
    if (index < 0 || index >= this->GetLength()) {
        throw IndexOutOfRange("operator[] error: index out of range");
    }
    return this->data.Get(index);
}

template <class T>
MutableArraySequence<T> MutableArraySequence<T>::operator+(const MutableArraySequence<T>& other) const {
    MutableArraySequence<T> result(*this);
    for (int i = 0; i < other.GetLength(); i++) {
        result.Append(other.Get(i));
    }
    return result;
}

template <class T>
MutableArraySequence<T>& MutableArraySequence<T>::operator+=(const T& value) {
    this->Append(value);
    return *this;
}

template <class T>
MutableArraySequence<T>& MutableArraySequence<T>::operator+=(const MutableArraySequence<T>& other) {
    for (int i = 0; i < other.GetLength(); i++) {
        this->Append(other.Get(i));
    }
    return *this;
}