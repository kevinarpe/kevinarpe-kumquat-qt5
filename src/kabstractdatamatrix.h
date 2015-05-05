//
// Created by kca on 5/2/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KABSTRACTDATAMATRIX_H
#define KEVINARPE_KUMQUAT_QT5_KABSTRACTDATAMATRIX_H

#include <cstddef>

namespace kumquat {

template<typename TValue>
class KAbstractDataMatrix {

public:
    KAbstractDataMatrix()
    { }

    virtual
    ~KAbstractDataMatrix()
    { }

    virtual std::size_t
    rowCount()
    const = 0;

    virtual std::size_t
    columnCount()
    const = 0;

    virtual const TValue&
    data(const std::size_t rowIndex, const std::size_t columnIndex)
    const = 0;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KABSTRACTDATAMATRIX_H
