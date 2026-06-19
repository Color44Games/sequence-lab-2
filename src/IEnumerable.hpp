#pragma once

#include "IEnumerator.hpp"

template <class T>
class IEnumerable {
public:
    virtual ~IEnumerable() {}

    virtual IEnumerator<T>* GetEnumerator() const = 0;
};