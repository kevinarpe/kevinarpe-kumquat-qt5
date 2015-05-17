//
// Created by kca on 5/13/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KROWDATAMATRIX_H
#define KEVINARPE_KUMQUAT_QT5_KROWDATAMATRIX_H

#include "knamespace"
#include "kglobal"
#include "kstdlib"
#include "KColumnCount"
#include <vector>
#include <sstream>

namespace kumquat {

template<typename TValue>
class KRowDataMatrix {

private:
    typedef std::vector<TValue> _ValueVec;

public:
    typedef KRowDataMatrix<TValue> Self;
    typedef typename _ValueVec::const_iterator const_iterator;

public:
    KRowDataMatrix(const KColumnCount& columnCount)
        : _columnCount(columnCount.value)
    { }

public:
    std::size_t
    size(const Dimension dim)
    const {
        if (Dimension::Row == dim) {
            const std::size_t x = _valueVec.size() / _columnCount;
            return x;
        }
        else if (Dimension::Column == dim) {
            return _columnCount;
        }
        else {
            assert(false && "Unreachable code");
        }
    }

public:
    const_iterator
    begin()
    const {
        const const_iterator x = _valueVec.begin();
        return x;
    }

public:
    const_iterator
    end()
    const {
        const const_iterator x = _valueVec.end();
        return x;
    }

public:
    const TValue&
    data(const std::size_t rowIndex, const std::size_t columnIndex)
    const {
        const std::size_t offset = (rowIndex * _columnCount) + columnIndex;
        const TValue& x = _valueVec[offset];
        return x;
    }
    // TODO: Maybe add safe_data() to use std::vector::at() for Python access (to catch exceptions)

private:
    template<typename InputIter>
    void
    _assertAppendSize(InputIter first, InputIter last) {
        const std::size_t size = std::size_t(std::distance(first, last));
        if (size != _columnCount) {
            // Ref: http://stackoverflow.com/a/11922409/257299
            std::ostringstream str;
            str << "Distince between arguments 'first' and 'last': Expected size " << _columnCount
                << ", but found " << size;
            kabort(str.str());
        }
    }

public:
    Self&
    append(std::initializer_list<TValue> list) {
        append(list.begin(), list.end());
        return *this;
    }

public:
    template<typename InputIter>
    Self&
    append(InputIter first, InputIter last) {
        _assertAppendSize(first, last);
        const std::size_t size = std::size_t(std::distance(first, last));
        const std::size_t newSize = _valueVec.capacity() + size;
        _valueVec.reserve(newSize);
        _valueVec.insert(_valueVec.end(), first, last);
        return *this;
    }

private:
    const std::size_t _columnCount;
    _ValueVec _valueVec;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KROWDATAMATRIX_H
