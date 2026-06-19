#pragma once

#include "Sequence.hpp"

// Геттеры
template <class T>
const T& Sequence<T>::GetFirst() const {
    if (this->GetLength() == 0) {
        throw EmptyCollectionError("GetFirst error: empty collection is given");
    }

    return this->Get(0);
}

template <class T>
const T& Sequence<T>::GetLast() const {
    if (this->GetLength() == 0) {
        throw EmptyCollectionError("GetLast error: empty collection is given");
    }
    return this->Get(this->GetLength() - 1);
}

template <class T>
Sequence<T>* Sequence<T>::GetSubsequence(int start_index, int end_index) const {
    if (start_index < 0 || end_index >= this->GetLength() || start_index > end_index) {
        throw IndexOutOfRange("GetSubsequence error: invalid indexes range");
    }

    int new_size = end_index - start_index + 1;
    ISequenceBuilder<T>* builder = this->CreateBuilder();

    for (int i = 0; i < new_size; i++) {
        builder->Append(this->Get(start_index + i));
    }

    Sequence<T>* sub_sequence = builder->Build();
    delete builder;

    return sub_sequence;
}

// Конкатенация
template <class T>
Sequence<T>* Sequence<T>::Concat(const Sequence<T>& other) const {
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

// Map-reduce
template <class T>
Sequence<T>* Sequence<T>::Map(T (*func)(T)) const {
    ISequenceBuilder<T>* builder = this->CreateBuilder();
    IEnumerator<T>* en = this->GetEnumerator();

    while (en->MoveNext()) {
        builder->Append(func(en->GetCurrent()));
    }

    Sequence<T>* result = builder->Build();
    delete builder;
    delete en;

    return result;
}

template <class T>
Sequence<T>* Sequence<T>::Where(bool (*predicate)(T)) const {
    ISequenceBuilder<T>* builder = this->CreateBuilder();
    IEnumerator<T>* en = this->GetEnumerator();

    while (en->MoveNext()) {
        if (predicate(en->GetCurrent())) {
            builder->Append(en->GetCurrent());
        }
    }

    Sequence<T>* result = builder->Build();
    delete builder;
    delete en;

    return result;
}

template <class T>
template <class T2>
T2 Sequence<T>::Reduce(T2 (*func)(T2, T), T initial) const {
    T2 accum = initial;
    IEnumerator<T>* en = this->GetEnumerator();

    while (en->MoveNext()) {
        accum = func(accum, en->GetCurrent());
    }

    delete en;

    return accum;
}

// Операторы
template <class T>
bool Sequence<T>::operator==(const Sequence<T>& other) const {
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
bool Sequence<T>::operator!=(const Sequence<T>& other) const {
    return !(*this == other);
}