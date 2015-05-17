//
// Created by kca on 5/17/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KMATRIXINDEX_H
#define KEVINARPE_KUMQUAT_QT5_KMATRIXINDEX_H

#include <cstdlib>
#include <functional>

namespace kumquat {

class KMatrixIndex /*final*/ {

public:
    KMatrixIndex(const std::size_t rowIndex, const std::size_t columnIndex)
        : _rowIndex(rowIndex), _columnIndex(columnIndex)
    { }

    std::size_t
    rowIndex()
    const {
        return _rowIndex;
    }

    std::size_t
    columnIndex()
    const {
        return _columnIndex;
    }

private:
    std::size_t _rowIndex;
    std::size_t _columnIndex;
};

inline
bool
operator<(const KMatrixIndex& a, const KMatrixIndex& b) {
    if (a.rowIndex() < b.rowIndex()) {
        return true;
    }
    const bool x = (a.columnIndex() < b.columnIndex());
    return x;
}

}  // namespace kumquat

namespace std {

// Specialisation of std::hash for all unscoped enums.
// Ref: http://stackoverflow.com/a/21029900/257299
template<>
class hash<kumquat::KMatrixIndex> {

public:
    size_t
    operator()(const kumquat::KMatrixIndex& value)
    const {
        const std::hash<size_t> h = std::hash<size_t>();

        const size_t rowIndex = value.rowIndex();
        const size_t rowIndexHash = h(rowIndex);

        const size_t columnIndex = value.columnIndex();
        const size_t columnIndexHash = h(columnIndex);

        const size_t x = (31 * rowIndexHash) + columnIndexHash;
        return x;
    }
};

}  // namespace std

#endif //KEVINARPE_KUMQUAT_QT5_KMATRIXINDEX_H
