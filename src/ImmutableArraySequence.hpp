#pragma once

#include "ArraySequence.hpp"

template <class T>
class ImmutableArraySequence : public ArraySequence<T> {
protected:
    ArraySequence<T>* Instance() override {
        return new ImmutableArraySequence<T>(*this);
    }

public:
    class Builder : public ISequenceBuilder<T> {
    private:
        ImmutableArraySequence<T>* seq;

    public:
        Builder() {
            this->seq = new ImmutableArraySequence();
        }

        virtual ~Builder() {
            delete this->seq;
        }

        ISequenceBuilder<T>* Append(const T& item) override {
            if (seq) {
                this->seq->AppendInternal(item);
            }
            return this;
        }

        ImmutableArraySequence<T>* Build() override {
            ImmutableArraySequence<T>* res = seq;
            this->seq = nullptr;
            return res;
        }
    };

    // Билдер
    ISequenceBuilder<T>* CreateBuilder() const override {
        return new Builder();
    }

    // Конструкторы и деструктор
    ImmutableArraySequence();
    explicit ImmutableArraySequence(int count);
    ImmutableArraySequence(T* items, int count);
    ImmutableArraySequence(const ArraySequence<T>& other);
    ImmutableArraySequence(const ImmutableArraySequence<T>& other);
    ImmutableArraySequence(ImmutableArraySequence<T>&& other) noexcept = default;
    ~ImmutableArraySequence();

    // Операторы (Разрешенные)
    const T& operator[](int index) const override;
    ImmutableArraySequence<T> operator+(const ImmutableArraySequence<T>& other) const;

    // Операторы (Запрещенные)
    ImmutableArraySequence<T>& operator=(const ImmutableArraySequence<T>& other) = delete;
    ImmutableArraySequence<T>& operator=(ImmutableArraySequence<T>&& other) noexcept = delete;
    ImmutableArraySequence<T>& operator+=(const T& value) = delete;
    ImmutableArraySequence<T>& operator+=(const ImmutableArraySequence<T>& value) = delete;

    // Collection override
    Sequence<T>* CreateEmpty() const override {
        return new ImmutableArraySequence<T>();
    }

    Sequence<T>* Copy() const override {
        return new ImmutableArraySequence<T>(*this);
    }
};

#include "ImmutableArraySequence.tpp"