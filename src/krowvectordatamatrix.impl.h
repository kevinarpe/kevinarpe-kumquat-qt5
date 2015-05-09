//
// Created by kca on 5/8/15.
//

#include "KRowVectorDataMatrix"

namespace kumquat {

// public virtual
template<typename TValue>
std::size_t
KRowVectorDataMatrix<TValue>::
rowCount()
const /*override*/ {
    const std::size_t x = _rowVecVec.size();
    return x;
}

// public virtual
template<typename TValue>
std::size_t
KRowVectorDataMatrix<TValue>::
columnCount()
const /*override*/ {
    const RowVec& rowVec = _rowVecVec.at(0);
    const std::size_t x = rowVec.size();
    return x;
}

// public virtual
template<typename TValue>
const TValue&
KRowVectorDataMatrix<TValue>::
data(std::size_t rowIndex, std::size_t columnIndex)
const /*override*/ {
    const RowVec& rowVec = _rowVecVec.at(rowIndex);
    const TValue& x = rowVec.at(columnIndex);
    return x;
}

// public virtual
template<typename TValue>
typename KRowVectorDataMatrix<TValue>::Self&
KRowVectorDataMatrix<TValue>::
appendRow(const RowVec& rowVec) {
    const RowVec rowVecCopy = RowVec(rowVec);
    _rowVecVec.push_back(rowVecCopy);
    return *this;
}

}  // namespace kumquat
