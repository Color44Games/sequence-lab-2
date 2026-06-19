#pragma once

#include "ImmutableArraySequence.hpp"

// Конструкторы и деструктор
template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence() : ArraySequence<T>() {}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(int count) : ArraySequence<T>(count) {}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const ArraySequence<T>& other) : ArraySequence<T>(other) {}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const ImmutableArraySequence<T>& other) : ArraySequence<T>(other) {}

template <class T>
ImmutableArraySequence<T>::~ImmutableArraySequence() {}

// Операторы
template <class T>
const T& ImmutableArraySequence<T>::operator[](int index) const {
    if (index < 0 || index >= this->GetLength()) {
        throw IndexOutOfRange("operator[] error: index out of range");
    }
    return this->data.Get(index);
}

template <class T>
ImmutableArraySequence<T> ImmutableArraySequence<T>::operator+(const ImmutableArraySequence<T>& other) const {
    ImmutableArraySequence<T> result(*this);
    for (int i = 0; i < other.GetLength(); i++) {
        result.AppendInternal(other.Get(i));
    }
    return result;
}