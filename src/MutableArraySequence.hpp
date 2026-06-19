#pragma once

#include "ArraySequence.hpp"

template <class T>
class MutableArraySequence : public ArraySequence<T> {
protected:
    ArraySequence<T>* Instance() override {
        return this;
    }

public:
    class Builder : public ISequenceBuilder<T> {
    private:
        MutableArraySequence<T>* seq;

    public:
        Builder() {
            seq = new MutableArraySequence();
        }

        virtual ~Builder() {
            delete seq;
        }

        ISequenceBuilder<T>* Append(const T& item) override {
            if (seq) {
                seq->AppendInternal(item);
            }
            return this;
        }

        MutableArraySequence<T>* Build() override {
            MutableArraySequence<T>* res = seq;
            seq = nullptr;
            return res;
        }
    };

    // Билдер
    ISequenceBuilder<T>* CreateBuilder() const override {
        return new Builder();
    }

    // Конструкторы и деструктор
    MutableArraySequence();
    explicit MutableArraySequence(int count);
    MutableArraySequence(T* items, int count);
    MutableArraySequence(const ArraySequence<T>& other);
    MutableArraySequence(const MutableArraySequence<T>& other);
    MutableArraySequence(MutableArraySequence<T>&& other) noexcept = default;
    ~MutableArraySequence();

    // Операторы
    MutableArraySequence<T>& operator=(const MutableArraySequence<T>& other);
    MutableArraySequence<T>& operator=(MutableArraySequence<T>&& other) noexcept = default;
    T& operator[](int index);
    const T& operator[](int index) const override;
    MutableArraySequence<T> operator+(const MutableArraySequence<T>& other) const;
    MutableArraySequence<T>& operator+=(const T& value);
    MutableArraySequence<T>& operator+=(const MutableArraySequence<T>& other);

    Sequence<T>* CreateEmpty() const override {
        return new MutableArraySequence<T>();
    }

    Sequence<T>* Copy() const override {
        return new MutableArraySequence<T>(*this);
    }
};

#include "MutableArraySequence.tpp"