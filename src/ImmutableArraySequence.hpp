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

    // Операторы
    ImmutableArraySequence();
    explicit ImmutableArraySequence(int count);
    ImmutableArraySequence(T* items, int count);
    ImmutableArraySequence(const ArraySequence<T>& other);
    ImmutableArraySequence(const ImmutableArraySequence<T>& other);
    ImmutableArraySequence(ImmutableArraySequence<T> &&other) noexcept = default;
    ~ImmutableArraySequence();

    ImmutableArraySequence<T>& operator=(const ImmutableArraySequence<T>& other);
    ImmutableArraySequence<T>& operator=(ImmutableArraySequence<T> &&other) noexcept = default;
    bool operator==(const ImmutableArraySequence<T>& other) const;
    bool operator!=(const ImmutableArraySequence<T>& other) const;
    const T& operator[](int index) const override;
    ImmutableArraySequence<T> operator+(const ImmutableArraySequence<T>& other) const;
    ImmutableArraySequence<T>& operator+=(const T& value);
    ImmutableArraySequence<T>& operator+=(const ImmutableArraySequence<T>& value);

    Sequence<T>* CreateEmpty() const override {
        return new ImmutableArraySequence<T>();
    }

    Sequence<T>* Copy() const override {
        return new ImmutableArraySequence<T>(*this);
    }
};

#include "ImmutableArraySequence.tpp"