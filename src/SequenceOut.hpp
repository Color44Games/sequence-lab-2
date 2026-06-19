#pragma once

#include <ostream>
#include "Sequence.hpp"

template <class T>
std::ostream& operator<<(std::ostream& os, const Sequence<T>& seq) {
    os << '[';
    
    bool first = true;
    IEnumerator<T>* en = seq.GetEnumerator();

    while (en->MoveNext()) {
        if (!first){
            os << ", ";
        }
        os << en->GetCurrent();
        first = false;
    }

    os << ']';
    delete en;

    return os;
}