//
// Created by kca on 5/2/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KROWARRAYDATAMATRIX_H
#define KEVINARPE_KUMQUAT_QT5_KROWARRAYDATAMATRIX_H

#include "KIDataMatrix"
#include <vector>

namespace kumquat {

template<typename TValue>
class KRowVectorDataMatrix
    : public KIDataMatrix<TValue> {

private:
    typedef KIDataMatrix<TValue> Base;

public:
    typedef KRowVectorDataMatrix<TValue> Self;
    typedef std::vector<TValue> RowVec;

    KRowVectorDataMatrix()
    : Base()
    { }

    virtual
    ~KRowVectorDataMatrix()
    { }

    virtual std::size_t
    size(Dimension dimension)
    const override;

    virtual const TValue&
    data(const std::size_t rowIndex, const std::size_t columnIndex)
    const override;

    virtual Self&
    appendRow(const RowVec& rowVec);

private:
    // TODO: Convert to use std::vector<TValue>
    // ... where offset = (rowIndex * columnCount) + columnIndex
    typedef std::vector<RowVec> _RowVecVec;
    _RowVecVec _rowVecVec;
};

}  // namespace kumquat

#include "krowvectordatamatrix.impl.h"

#endif //KEVINARPE_KUMQUAT_QT5_KROWARRAYDATAMATRIX_H
