#pragma once

template <class T>
class Sequence;

template <class T>
class ISequenceBuilder {
public:
    virtual ~ISequenceBuilder() {}

    virtual ISequenceBuilder<T>* Append(const T& item) = 0;
    virtual Sequence<T>* Build() = 0;
};