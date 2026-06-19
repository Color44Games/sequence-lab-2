#pragma once

#include "Sequence.hpp"
#include "LinkedList.hpp"

template <class T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T> data;

public:
    // Конструкторы и деструктор
    ListSequence();
    ListSequence(T* items, int count);
    ListSequence(const ListSequence<T>& list);
    ListSequence(ListSequence<T> &&other) noexcept = default;
    ~ListSequence();

    // Sequence override
    const T& Get(int index) const override;
    int GetLength() const override;
    const T& GetFirst() const override;
    const T& GetLast() const override;
    Sequence<T>* Append(T item) override;
    Sequence<T>* Prepend(T item) override;
    Sequence<T>* InsertAt(T item, int index) override;

    // Геттер
    IEnumerator<T>* GetEnumerator() const override;

    // Оператор
    ListSequence<T>& operator=(ListSequence<T> &&other) noexcept = default;

protected:
    virtual ListSequence<T>* Instance() = 0;
    ListSequence<T>* AppendInternal(T item);
    ListSequence<T>* PrependInternal(T item);
    ListSequence<T>* InsertAtInternal(T item, int index);
};

#include "ListSequence.tpp"