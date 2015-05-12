//
// Created by kca on 5/2/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KABSTRACTDATAMATRIX_H
#define KEVINARPE_KUMQUAT_QT5_KABSTRACTDATAMATRIX_H

#include "knamespace"
#include <cstddef>

namespace kumquat {

template<typename TValue>
class KIDataMatrix {

public:
    KIDataMatrix()
    { }

    virtual
    ~KIDataMatrix()
    { }

    virtual std::size_t
    size(Dimension dimension)
    const = 0;

    virtual const TValue&
    data(const std::size_t rowIndex, const std::size_t columnIndex)
    const = 0;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KABSTRACTDATAMATRIX_H
