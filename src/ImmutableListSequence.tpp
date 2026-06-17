#pragma once

#include "ImmutableListSequence.hpp"

template <class T>
ImmutableListSequence<T>::ImmutableListSequence() : ListSequence<T>() {}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(const ListSequence<T>& other) : ListSequence<T> (other) {}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(const ImmutableListSequence<T>& other) : ListSequence<T> (other) {}

template <class T>
ImmutableListSequence<T>::~ImmutableListSequence() {}

template <class T>
ImmutableListSequence<T>& ImmutableListSequence<T>::operator=(const ImmutableListSequence<T>& other) {
    if (this != &other) {
        this->data = other.data;
    }
    return *this;
}

template <class T>
bool ImmutableListSequence<T>::operator==(const ImmutableListSequence<T>& other) const {
    if (this->GetLength() != other.GetLength()) {
        return false;
    }

    for (int i = 0; i < this->GetLength(); i++) {
        if (this->Get(i) != other.Get(i)) {
            return false;
        }
    }
    return true;
}

template <class T>
bool ImmutableListSequence<T>::operator!=(const ImmutableListSequence<T>& other) const {
    return !(*this == other);
}

template <class T>
const T& ImmutableListSequence<T>::operator[](int index) const {
    if (index < 0 || index >= this->GetLength()) {
        throw IndexOutOfRange("operator[] error: index out of range");
    }

    IEnumerator<T>* curr = this->GetEnumerator();
    curr->MoveNext();
    for (int i = 0; i < index; i++) {
        curr->MoveNext();
    }
    const T& val = curr->GetCurrent();
    delete curr;
    return val;
}

template <class T>
ImmutableListSequence<T> ImmutableListSequence<T>::operator+(const ImmutableListSequence<T>& other) const {
    ImmutableListSequence<T> result(*this);
    for (int i = 0; i < other.GetLength(); i++) {
        result.AppendInternal(other.Get(i));
    }
    return result;
}

template <class T>
ImmutableListSequence<T> &ImmutableListSequence<T>::operator+=(const T& value) {
    ImmutableListSequence<T> result(*this);
    result.AppendInternal(value);
    *this = result;
    return *this;
}

template <class T>
ImmutableListSequence<T> &ImmutableListSequence<T>::operator+=(const ImmutableListSequence<T>& other) {
    ImmutableListSequence<T> result(*this);
    for (int i = 0; i < other.GetLength(); i++) {
        result.AppendInternal(other.Get(i));
    }
    *this = result;
    return *this;
}