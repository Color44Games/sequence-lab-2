#pragma once

#include "DynamicArray.hpp"
#include "Sequence.hpp"


template <class T>
class ArraySequence : public Sequence<T> {
protected:
    int size;              // Текущий размер
    DynamicArray<T> data;  // data.size - вместимость

public:
    class Enumerator : public IEnumerator<T> {
    private:
        const ArraySequence<T>* seq;
        int curr_index;

    public:
        explicit Enumerator(const ArraySequence<T>* ptr) : seq(ptr), curr_index(-1) {}

        bool MoveNext() override {
            if (this->curr_index + 1 < this->seq->GetLength()) {
                this->curr_index++;
                return true;
            }
            return false;
        }

        const T& GetCurrent() const override {
            if (this->curr_index < 0 || this->curr_index >= this->seq->GetLength()) {
                throw IndexOutOfRange("Enumerator error: index out of range");
            }
            return this->seq->Get(curr_index);
        }

        void Reset() override {
            this->curr_index = -1;
        }
    };

    // Конструкторы и деструктор
    ArraySequence();
    explicit ArraySequence(int count);
    ArraySequence(T* items, int count);
    ArraySequence(const ArraySequence<T>& other);
    ArraySequence(ArraySequence<T>&& other) noexcept = default;
    ~ArraySequence();

    // Sequence override
    const T& Get(int index) const override;
    int GetLength() const override;
    const T& GetFirst() const override;
    const T& GetLast() const override;
    Sequence<T>* Append(T item) override;
    Sequence<T>* Prepend(T item) override;
    Sequence<T>* InsertAt(T item, int index) override;

    // Геттеры
    int GetCapacity() const;
    IEnumerator<T>* GetEnumerator() const override;

    // Оператор
    ArraySequence<T>& operator=(ArraySequence<T>&& other) noexcept = default;

protected:
    virtual ArraySequence<T>* Instance() = 0;
    ArraySequence<T>* AppendInternal(T item);
    ArraySequence<T>* PrependInternal(T item);
    ArraySequence<T>* InsertAtInternal(T item, int index);
};

#include "ArraySequence.tpp"