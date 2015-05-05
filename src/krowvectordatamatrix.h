//
// Created by kca on 5/2/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KROWARRAYDATAMATRIX_H
#define KEVINARPE_KUMQUAT_QT5_KROWARRAYDATAMATRIX_H

#include "kabstractdatamatrix.h"
#include <vector>

namespace kumquat {

template<typename TValue>
class KRowVectorDataMatrix : public KAbstractDataMatrix<TValue> {

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

public:
    virtual std::size_t
    rowCount()
    const override {
        const std::size_t x = _rowVecVec.size();
        return x;
    }

public:
    virtual std::size_t
    columnCount()
    const override {
        const RowVec& rowVec = _rowVecVec.at(0);
        const std::size_t x = rowVec.size();
        return x;
    }

public:
    virtual const TValue&
    data(std::size_t rowIndex, std::size_t columnIndex)
    const override {
        const RowVec& rowVec = _rowVecVec.at(rowIndex);
        const TValue& x = rowVec.at(columnIndex);
        return x;
    }

public:
    virtual Self&
    appendRow(const RowVec& rowVec) {
        const RowVec rowVecCopy = RowVec(rowVec);
        _rowVecVec.push_back(rowVecCopy);
        return *this;
    }

private:
    typedef std::vector<RowVec> _RowVecVec;
    _RowVecVec _rowVecVec;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KROWARRAYDATAMATRIX_H
