#pragma once

#include "ListSequence.hpp"

template <class T>
class MutableListSequence : public ListSequence<T> {
protected:
    ListSequence<T>* Instance() override {
        return this;
    }

public:
    class Builder : public ISequenceBuilder<T> {
    private:
        MutableListSequence<T>* seq;

    public:
        Builder() {
            seq = new MutableListSequence();
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

        MutableListSequence<T>* Build() override {
            MutableListSequence<T> *res = seq;
            seq = nullptr;
            return res;
        }
    };

    // Билдер
    ISequenceBuilder<T>* CreateBuilder() const override {
        return new Builder();
    }

    // Конструкторы и деструктор
    MutableListSequence();
    MutableListSequence(T* items, int count);
    MutableListSequence(const ListSequence<T>& other);
    MutableListSequence(const MutableListSequence<T>& other);
    MutableListSequence(MutableListSequence<T> &&other) noexcept = default;
    ~MutableListSequence();

    // Операторы
    MutableListSequence<T>& operator=(const MutableListSequence<T>& other);
    MutableListSequence<T>& operator=(MutableListSequence<T> &&other) noexcept = default;
    bool operator==(const MutableListSequence<T>& other) const;
    bool operator!=(const MutableListSequence<T>& other) const;
    T& operator[](int index);
    const T& operator[](int index) const override;
    MutableListSequence<T> operator+(const MutableListSequence<T>& other) const;
    MutableListSequence<T>& operator+=(const T& value);
    MutableListSequence<T>& operator+=(const MutableListSequence<T>& other);

    Sequence<T>* CreateEmpty() const override { 
        return new MutableListSequence<T>(); 
    }

    Sequence<T>* Copy() const override {
        return new MutableListSequence<T>(*this);
    }
};

#include "MutableListSequence.tpp"