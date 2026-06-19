#pragma once

#include "ArraySequence.hpp"

#define INITIAL_CAPACITY 8

// Конструкторы и деструктор
template <class T>
ArraySequence<T>::ArraySequence() : size(0), data(INITIAL_CAPACITY) {}

template <class T>
ArraySequence<T>::ArraySequence(int count) : size(count), data(count * 2) {
    for (int i = 0; i < count; i++) {
        data[i] = T();
    }
}

template <class T>
ArraySequence<T>::ArraySequence(T* items, int count) : size(count), data(items, count) {}

template <class T>
ArraySequence<T>::ArraySequence(const ArraySequence& other) : size(other.size), data(other.data) {}

template <class T>
ArraySequence<T>::~ArraySequence() {}

// Sequence override
template <class T>
const T& ArraySequence<T>::Get(int index) const {
    if (index < 0 || index >= this->size) {
        throw IndexOutOfRange("Get error: index out of range");
    }
    return this->data.Get(index);
}

template <class T>
int ArraySequence<T>::GetLength() const {
    return this->size;
}

template <class T>
const T& ArraySequence<T>::GetFirst() const {
    if (this->size == 0) {
        throw EmptyCollectionError("GetFirst error: empty collection is given");
    }
    return this->data.Get(0);
}

template <class T>
const T& ArraySequence<T>::GetLast() const {
    if (this->size == 0) {
        throw EmptyCollectionError("GetLast error: empty collection is given");
    }
    return this->data.Get(this->size - 1);
}

template <class T>
Sequence<T>* ArraySequence<T>::Append(T item) {
    return this->Instance()->AppendInternal(item);
}

template <class T>
Sequence<T>* ArraySequence<T>::Prepend(T item) {
    return this->Instance()->PrependInternal(item);
}

template <class T>
Sequence<T>* ArraySequence<T>::InsertAt(T item, int index) {
    return this->Instance()->InsertAtInternal(item, index);
}

// Геттеры
template <class T>
int ArraySequence<T>::GetCapacity() const {
    return this->data.GetSize();
}


template <class T>
IEnumerator<T>* ArraySequence<T>::GetEnumerator() const {
    return new Enumerator(this);
}

// Внутренние методы
template <class T>
ArraySequence<T>* ArraySequence<T>::AppendInternal(T item) {
    if (this->data.GetSize() <= this->size) {
        this->data.Resize(this->size * 2);
    }

    this->size++;
    this->data.Set(this->size - 1, item);

    return this;
}

template <class T>
ArraySequence<T>* ArraySequence<T>::PrependInternal(T item) {
    if (this->data.GetSize() <= this->size) {
        this->data.Resize(this->size * 2);
    }

    this->size++;
    for (int i = this->size - 1; i > 0; i--) {
        this->data.Set(i, this->data.Get(i - 1));
    }
    this->data.Set(0, item);

    return this;
}

template <class T>
ArraySequence<T>* ArraySequence<T>::InsertAtInternal(T item, int index) {
    if (index < 0 || index > this->data.GetSize()) {
        throw IndexOutOfRange("InsertAt error: index out of range");
    }

    if (this->data.GetSize() <= this->size) {
        this->data.Resize(this->size * 2);
    }

    this->size++;
    for (int i = this->size - 1; i > index; i--) {
        this->data.Set(i, this->data.Get(i - 1));
    }
    this->data.Set(index, item);

    return this;
}