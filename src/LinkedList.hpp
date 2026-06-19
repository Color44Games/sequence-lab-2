#pragma once

#include "Exceptions.hpp"
#include "IEnumerable.hpp"

template <class T>
class LinkedList : public IEnumerable<T> {
public:
    struct Node
    {
        T val;
        Node* next;
        Node* prev;
    };

private:
    int size;
    Node* head;
    Node* tail;

public:
    class Enumerator : public IEnumerator<T> {
    private:
        const Node* head;
        const Node* curr;
        bool started;

    public:
        explicit Enumerator(const Node* ptr) : head(ptr), curr(nullptr), started(false) {}

        bool MoveNext() override {
            if (!this->started) {
                this->started = true;
                this->curr = head;
            } else if (this->curr != nullptr) {
                this->curr = this->curr->next;
            }
            return this->curr != nullptr;
        }

        const T& GetCurrent() const override {
            if (curr == nullptr) {
                throw IndexOutOfRange("Enumerator error: curr in nullptr");
            }
            return curr->val;
        }

        void Reset() override {
            this->curr = nullptr;
            this->started = false;
        }
    };

    // Конструкторы и деструктор
    LinkedList();
    LinkedList(T* items, int count);
    LinkedList(const LinkedList<T>& list);
    LinkedList(LinkedList<T>&& other) noexcept;
    ~LinkedList();

    // Геттеры
    const T& GetFirst() const;
    const T& GetLast() const;
    const T& Get(int index) const;
    LinkedList<T>* GetSubList(int start_index, int end_index) const;
    int GetLength() const;
    IEnumerator<T>* GetEnumerator() const override;
    const Node* GetHead() const;
    const Node* GetTail() const;

    // Операции
    void Append(T item);
    void Prepend(T item);
    void InsertAt(T item, int index);
    T RemoveAt(int index);
    LinkedList<T>* Concat(const LinkedList<T>& list);

    // Операторы
    LinkedList<T>& operator=(const LinkedList<T>& other);
    LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
};

#include "LinkedList.tpp"