#pragma once

#include "ImmutableListSequence.hpp"

// Конструкторы и деструктор
template <class T>
ImmutableListSequence<T>::ImmutableListSequence() : ListSequence<T>() {}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(const ListSequence<T>& other) : ListSequence<T>(other) {}

template <class T>
ImmutableListSequence<T>::ImmutableListSequence(const ImmutableListSequence<T>& other) : ListSequence<T>(other) {}

template <class T>
ImmutableListSequence<T>::~ImmutableListSequence() {}

// Операторы
template <class T>
const T& ImmutableListSequence<T>::operator[](int index) const {
    if (index < 0 || index >= this->GetLength()) {
        throw IndexOutOfRange("operator[] error: index out of range");
    }

    auto* curr = this->data.GetHead();
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr->val;
}

template <class T>
ImmutableListSequence<T> ImmutableListSequence<T>::operator+(const ImmutableListSequence<T>& other) const {
    ImmutableListSequence<T> result(*this);
    for (int i = 0; i < other.GetLength(); i++) {
        result.AppendInternal(other.Get(i));
    }
    return result;
}