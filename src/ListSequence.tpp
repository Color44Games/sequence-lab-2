#pragma once

#include "ListSequence.hpp"

// Конструкторы и деструктор
template <class T>
ListSequence<T>::ListSequence() : data() {}

template <class T>
ListSequence<T>::ListSequence(T* items, int count) : data(items, count) {}

template <class T>
ListSequence<T>::ListSequence(const ListSequence<T>& other) : data(other.data) {}

template <class T>
ListSequence<T>::~ListSequence() {}

// Sequence override
template <class T>
const T& ListSequence<T>::Get(int index) const {
    return this->data.Get(index);
}

template <class T>
int ListSequence<T>::GetLength() const {
    return this->data.GetLength();
}

template <class T>
const T& ListSequence<T>::GetFirst() const {
    return this->data.GetFirst();
}

template <class T>
const T& ListSequence<T>::GetLast() const {
    return this->data.GetLast();
}

template <class T>
Sequence<T>* ListSequence<T>::GetSubsequence(int start_index, int end_index) const {
    if (start_index < 0 || end_index >= this->data.GetLength() || start_index > end_index) {
        throw IndexOutOfRange("GetSubsequence error: invalid indexes range");
    }

    int new_size = end_index - start_index + 1;
    ISequenceBuilder<T>* builder = this->CreateBuilder();

    for (int i = 0; i < new_size; i++) {
        builder->Append(this->data.Get(start_index + i));
    }

    Sequence<T>* sub_sequence = builder->Build();
    delete builder;

    return sub_sequence;
}

template <class T>
Sequence<T>* ListSequence<T>::Append(T item) {
    return Instance()->AppendInternal(item);
}

template <class T>
Sequence<T>* ListSequence<T>::Prepend(T item) {
    return Instance()->PrependInternal(item);
}

template <class T> 
Sequence<T>* ListSequence<T>::InsertAt(T item, int index) {
    return Instance()->InsertAtInternal(item, index);
}

template <class T>
Sequence<T>* ListSequence<T>::Concat(const Sequence<T>& other) const {
    ISequenceBuilder<T>* builder = this->CreateBuilder();

    for (int i = 0; i < this->GetLength(); i++) {
        builder->Append(this->Get(i));
    }

    for (int i = 0; i < other.GetLength(); i++) {
        builder->Append(other.Get(i));
    }

    Sequence<T>* result = builder->Build();
    delete builder;

    return result;
}

// Геттер
template <class T>
IEnumerator<T>* ListSequence<T>::GetEnumerator() const {
    return this->data.GetEnumerator();
}

// Внутренние методы
template <class T>
ListSequence<T>* ListSequence<T>::AppendInternal(T item) { 
    data.Append(item);
    return this;
 }

template <class T>
ListSequence<T>* ListSequence<T>::PrependInternal(T item) { 
    data.Prepend(item); 
    return this; 
}

template <class T>
ListSequence<T>* ListSequence<T>::InsertAtInternal(T item, int index) { 
    data.InsertAt(item, index); 
    return this; 
}
