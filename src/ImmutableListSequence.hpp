#pragma once

#include "ListSequence.hpp"

template <class T>
class ImmutableListSequence : public ListSequence<T> {
protected:
    ListSequence<T>* Instance() override { 
        return new ImmutableListSequence<T>(*this); 
    }

public:
    class Builder : public ISequenceBuilder<T> {
    private:
        ImmutableListSequence<T>* seq;

    public:
        Builder() {
            seq = new ImmutableListSequence();
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

        ImmutableListSequence<T>* Build() override {
            ImmutableListSequence<T>* res = seq;
            seq = nullptr;
            return res;
        }
    };

    // Билдер
    ISequenceBuilder<T>* CreateBuilder() const override {
        return new Builder();
    }
    
    // Конструкторы и деструктор
    ImmutableListSequence();
    ImmutableListSequence(T* items, int count);
    ImmutableListSequence(const ListSequence<T>& other);
    ImmutableListSequence(const ImmutableListSequence<T>& other);
    ImmutableListSequence(ImmutableListSequence<T> &&other) noexcept = default;
    ~ImmutableListSequence();

    // Операторы
    ImmutableListSequence<T>& operator=(const ImmutableListSequence<T>& other);
    ImmutableListSequence<T>& operator=(ImmutableListSequence<T> &&other) noexcept = default;
    bool operator==(const ImmutableListSequence<T>& other) const;
    bool operator!=(const ImmutableListSequence<T>& other) const;
    const T& operator[](int index) const override;
    ImmutableListSequence<T> operator+(const ImmutableListSequence<T>& other) const;
    ImmutableListSequence<T>& operator+=(const T& value);
    ImmutableListSequence<T>& operator+=(const ImmutableListSequence<T>& other);

    Sequence<T>* CreateEmpty() const override { 
        return new ImmutableListSequence<T>(); 
    }

    Sequence<T>* Copy() const override {
        return new ImmutableListSequence<T>(*this);
    }
};

#include "ImmutableListSequence.tpp"