#pragma once
#include "LinkedList.hpp"

// Конструкторы и деструктор
template <class T>
LinkedList<T>::LinkedList() : size(0), head(nullptr), tail(nullptr) {}

template <class T>
LinkedList<T>::LinkedList(T* items, int count) : LinkedList() {
    if (count < 0) {
        throw IndexOutOfRange("LinkedList error: negative count");
    }

    if (count > 0 && items == nullptr) {
        throw InvalidArgument("LinkedList error: source ptr is nullptr");
    }

    for (int i = 0; i < count; i++) {
        this->Append(items[i]);
    }
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : LinkedList() {
    Node* curr = other.head;
    while (curr != nullptr) {
        this->Append(curr->val);
        curr = curr->next;
    }
}

template <class T>
LinkedList<T>::LinkedList(LinkedList<T>&& other) noexcept : size(other.size), head(other.head), tail(other.tail) {
    other.size = 0;
    other.head = nullptr;
    other.tail = nullptr;
}

template <class T>
LinkedList<T>::~LinkedList() {
    Node* curr = this->head;
    while (curr != nullptr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
}

// Декомпозиция
template <class T>
const T& LinkedList<T>::GetFirst() const {
    if (this->head == nullptr) {
        throw EmptyCollectionError("GetFirst error: empty list");
    }
    return this->head->val;
}

template <class T>
const T& LinkedList<T>::GetLast() const {
    if (this->tail == nullptr) {
        throw EmptyCollectionError("GetLast error: empty list");
    }
    return this->tail->val;
}

template <class T>
const T& LinkedList<T>::Get(int index) const {
    if (index < 0 || index >= this->size) {
        throw("Get error: index out of range");
    }
    Node* curr = this->head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr->val;
}

template <class T>
LinkedList<T>* LinkedList<T>::GetSubList(int start_index, int end_index) const {
    if (start_index < 0 || end_index >= this->size || start_index > end_index) {
        throw IndexOutOfRange("GetSubList error: invalid indexes range");
    }

    if (this->head == nullptr) {
        throw EmptyCollectionError("GetSubList error: empty collection is given");
    }

    LinkedList<T>* sub_list = new LinkedList<T>();
    Node* curr = this->head;

    for (int i = 0; i < start_index; i++) {
        curr = curr->next;
    }

    for (int i = start_index; i < end_index; i++) {
        sub_list->Append(curr->val);
        curr = curr->next;
    }
    return sub_list;
}

template <class T>
int LinkedList<T>::GetLength() const {
    return this->size;
}

template <class T>
IEnumerator<T>* LinkedList<T>::GetEnumerator() const {
    return new Enumerator(this->head);
}

template <class T>
const typename LinkedList<T>::Node* LinkedList<T>::GetHead() const {
    return this->head;
}

template <class T>
const typename LinkedList<T>::Node* LinkedList<T>::GetTail() const {
    return this->tail;
}

// Операции
template <class T>
void LinkedList<T>::Append(T item) {
    Node* new_node = new Node{item, nullptr, this->tail};
    if (this->size == 0) {
        this->head = new_node;
        this->tail = new_node;
    } else {
        this->tail->next = new_node;
        this->tail = new_node;
    }
    this->size++;
}

template <class T>
void LinkedList<T>::Prepend(T item) {
    Node* new_node = new Node{item, this->head, nullptr};
    if (this->size == 0) {
        this->head = new_node;
        this->tail = new_node;
    } else {
        this->head->prev = new_node;
        this->head = new_node;
    }
    this->size++;
}

template <class T>
void LinkedList<T>::InsertAt(T item, int index) {
    if (index < 0 || index > this->size) {
        throw IndexOutOfRange("InsertAt error: index out of range");
    }

    if (index == 0) {
        this->Prepend(item);
        return;
    }

    if (index == this->size) {
        this->Append(item);
        return;
    }

    Node* newNode = new Node{item, nullptr, nullptr};

    Node* current = this->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    Node* previous = current->prev;

    previous->next = newNode;
    newNode->prev = previous;

    newNode->next = current;
    current->prev = newNode;

    this->size++;
}

template <class T>
T LinkedList<T>::RemoveAt(int index) {
    if (this->size == 0) {
        throw EmptyCollectionError("RemoveAt error: empty collection is given");
    }

    if (index < 0 || index > this->size) {
        throw IndexOutOfRange("RemoveAt error: index out of range");
    }

    Node* curr = this->head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }

    T removedVal = curr->val;

    if (curr->prev != nullptr) {
        curr->prev->next = curr->next;
    } else {
        this->head = curr->next;
    }

    if (curr->next != nullptr) {
        curr->next->prev = curr->prev;
    } else {
        this->tail = curr;
    }

    delete curr;
    this->size--;

    return removedVal;
}

template <class T>
LinkedList<T>* LinkedList<T>::Concat(const LinkedList<T>& list) {
    LinkedList<T>* new_list = new LinkedList<T>(*this);
    if (list != nullptr) {
        Node* curr = list.head;
        while (curr != nullptr) {
            new_list->Append(curr->val);
            curr = curr->next;
        }
    }
    return new_list;
}

// Операторы
template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this != &other) {
        LinkedList<T> temp(other);

        Node* curr = this->head;
        while (curr != nullptr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
        this->head = nullptr;
        this->tail = nullptr;
        size = 0;

        this->head = temp.head;
        this->tail = temp.tail;
        this->size = temp.size;

        temp.head = nullptr;
        temp.tail = nullptr;
        temp.size = 0;
    }
    return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
    if (this != &other) {
        Node* curr = this->head;
        while (curr != nullptr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }

        this->head = other.head;
        this->tail = other.tail;
        this->size = other.size;

        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
    return *this;
}