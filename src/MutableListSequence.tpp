#pragma once

#include "MutableListSequence.hpp"

template <class T>
MutableListSequence<T>::MutableListSequence() : ListSequence<T>() {}

template <class T>
MutableListSequence<T>::MutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}

template <class T>
MutableListSequence<T>::MutableListSequence(const ListSequence<T>& other) : ListSequence<T> (other) {}

template <class T>
MutableListSequence<T>::MutableListSequence(const MutableListSequence<T>& other) : ListSequence<T> (other) {}

template <class T>
MutableListSequence<T>::~MutableListSequence() {}

template <class T>
MutableListSequence<T>& MutableListSequence<T>::operator=(const MutableListSequence<T>& other) {
    if (this != &other) {
        this->data = other.data;
    }
    return *this;
}

template <class T>
bool MutableListSequence<T>::operator==(const MutableListSequence<T>& other) const {
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
bool MutableListSequence<T>::operator!=(const MutableListSequence<T>& other) const {
    return !(*this == other);
}

template <class T>
T& MutableListSequence<T>::operator[](int index) {
    if (index < 0 || index >= this->GetLength()) {
        throw IndexOutOfRange("operator[] error: index out of range");
    }

    typename LinkedList<T>::Node* curr = this->data.GetHead();
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    T& value = curr->val;

    return value;
}

template <class T>
const T &MutableListSequence<T>::operator[](int index) const {
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
MutableListSequence<T> MutableListSequence<T>::operator+(const MutableListSequence<T>& other) const {
    MutableListSequence<T> result(*this);
    for (int i = 0; i < other.GetLength(); i++) {
        result.Append(other.Get(i));
    }
    return result;
}

template <class T>
MutableListSequence<T>& MutableListSequence<T>::operator+=(const T& value) {
    this->Append(value);
    return *this;
}

template <class T>
MutableListSequence<T>& MutableListSequence<T>::operator+=(const MutableListSequence<T>& other) {
    for (int i = 0; i < other.GetLength(); i++) {
        this->Append(other.Get(i));
    }
    return *this;
}