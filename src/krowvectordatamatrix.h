//
// Created by kca on 5/2/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KROWARRAYDATAMATRIX_H
#define KEVINARPE_KUMQUAT_QT5_KROWARRAYDATAMATRIX_H

#include "KAbstractDataMatrix"
#include <vector>

namespace kumquat {

template<typename TValue>
class KRowVectorDataMatrix
    : public KAbstractDataMatrix<TValue> {

private:
    typedef KAbstractDataMatrix<TValue> Base;

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
    rowCount()
    const override;

    virtual std::size_t
    columnCount()
    const override;

    virtual const TValue&
    data(std::size_t rowIndex, std::size_t columnIndex)
    const override;

    virtual Self&
    appendRow(const RowVec& rowVec);

private:
    typedef std::vector<RowVec> _RowVecVec;
    _RowVecVec _rowVecVec;
};

}  // namespace kumquat

#include "krowvectordatamatrix.impl.h"

#endif //KEVINARPE_KUMQUAT_QT5_KROWARRAYDATAMATRIX_H
