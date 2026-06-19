#pragma once

#include "Exceptions.hpp"
#include "ICollection.hpp"
#include "IEnumerable.hpp"
#include "ISequenceBuilder.hpp"

template <class T>
class Sequence : public ICollection<T>, public IEnumerable<T> {
public:
    // Билдер
    virtual ISequenceBuilder<T>* CreateBuilder() const = 0;

    // Геттеры
    const T& Get(int index) const override = 0;
    int GetLength() const override = 0;
    virtual const T& GetFirst() const;
    virtual const T& GetLast() const;
    virtual Sequence<T>* GetSubsequence(int start_index, int end_index) const;

    // Виртуальные конструкторы из ICollection
    Sequence<T>* CreateEmpty() const override = 0;
    Sequence<T>* Copy() const override = 0;

    // Операции
    virtual Sequence<T>* Append(T item) = 0;
    virtual Sequence<T>* Prepend(T item) = 0;
    virtual Sequence<T>* InsertAt(T item, int index) = 0;
    virtual Sequence<T>* Concat(const Sequence<T>& other) const;

    // Map, where, reduce
    virtual Sequence<T>* Map(T (*func)(T)) const;
    virtual Sequence<T>* Where(bool (*predicate)(T)) const;

    template <class T2>
    T2 Reduce(T2 (*func)(T2, T), T initial) const;

    // Операторы
    virtual const T& operator[](int index) const = 0;
    bool operator==(const Sequence<T>& other) const;
    bool operator!=(const Sequence<T>& other) const;

    // Деструктор
    virtual ~Sequence() {};
};

#include "Sequence.tpp"