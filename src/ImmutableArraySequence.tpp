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
ImmutableArraySequence<T>::ImmutableArraySequence(const ArraySequence<T>& other) : ArraySequence<T> (other) {}

template <class T>
ImmutableArraySequence<T>::ImmutableArraySequence(const ImmutableArraySequence<T>& other) : ArraySequence<T> (other) {}

template <class T>
ImmutableArraySequence<T>::~ImmutableArraySequence() {}

// Операторы
template <class T>
ImmutableArraySequence<T>& ImmutableArraySequence<T>::operator=(const ImmutableArraySequence<T>& other) {
	if (this != &other) {
		this->size = other.size;
		this->data = other.data;
	}
	return *this;
}

template <class T>
bool ImmutableArraySequence<T>::operator==(const ImmutableArraySequence<T>& other) const {
	if (this->GetLength() != other.GetLength()) return false;
	for (int i = 0; i < this->GetLength(); i++) {
		if (this->Get(i) != other.Get(i)) {
            return false;
        }
	}
	return true;
}

template <class T>
bool ImmutableArraySequence<T>::operator!=(const ImmutableArraySequence<T>& other) const {
	return !(*this == other);
}

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

template <class T>
ImmutableArraySequence<T>& ImmutableArraySequence<T>::operator+=(const T& value) {
	ImmutableArraySequence<T> result(*this);
	result.AppendInternal(value);
	*this = result;
	return *this;
}

template <class T>
ImmutableArraySequence<T>& ImmutableArraySequence<T>::operator+=(const ImmutableArraySequence<T>& other) {
	ImmutableArraySequence<T> result(*this);
	for (int i = 0; i < other.GetLength(); i++) {
		result.AppendInternal(other.Get(i));
	}
    *this = result;
	return *this;
}
