#pragma once

#include "Exceptions.hpp"
#include "IEnumerable.hpp"


template <class T>
class DynamicArray : public IEnumerable<T> {
private:
    T* data;
    int size;

public:
    class Enumerator : public IEnumerator<T> {
    private:
        const DynamicArray<T>* arr;
        int curr_index;

    public:
        explicit Enumerator(const DynamicArray<T>* ptr) : arr(ptr), curr_index(-1) {}

        bool MoveNext() override {
            if (this->curr_index + 1 < this->arr->GetSize()) {
                this->curr_index++;
                return true;
            }
            return false;
        }

        const T& GetCurrent() const override {
            if (this->curr_index < 0 || this->curr_index >= this->arr->GetSize()) {
                throw IndexOutOfRange("Enumerator error: index out of range");
            }
            return this->arr->data[this->curr_index];
        }

        void Reset() override {
            this->curr_index = -1;
        }
    };

    // Конструкторы и деструктор
    DynamicArray();
    explicit DynamicArray(int count);
    DynamicArray(T* items, int count);
    DynamicArray(const DynamicArray& other);
    DynamicArray(DynamicArray&& other) noexcept;
    ~DynamicArray();

    // Геттеры, сеттеры и resize
    void Set(int index, T value);
    const T& Get(int index) const;
    int GetSize() const;
    IEnumerator<T>* GetEnumerator() const override;
    void Resize(int new_size);

    // Операторы
    DynamicArray<T>& operator=(const DynamicArray<T>& other);
    DynamicArray<T>& operator=(DynamicArray<T>&& other) noexcept;
    T& operator[](int index);
    const T& operator[](int index) const;
};

#include "DynamicArray.tpp"