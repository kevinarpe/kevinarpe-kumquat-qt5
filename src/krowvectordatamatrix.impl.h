//
// Created by kca on 5/8/15.
//

#include "KRowVectorDataMatrix"
#include <cassert>

namespace kumquat {

// public virtual
template<typename TValue>
std::size_t
KRowVectorDataMatrix<TValue>::
size(Dimension dimension)
const /*override*/ {
    switch (dimension) {
        case Dimension::Row: {
            const std::size_t x = _rowVecVec.size();
            return x;
            break;
        }
        case Dimension::Column: {
            const RowVec& rowVec = _rowVecVec.at(0);
            const std::size_t x = rowVec.size();
            return x;
            break;
        }
        default: {
            assert(false && "Unreachable code");
        }
    }
}

// public virtual
template<typename TValue>
const TValue&
KRowVectorDataMatrix<TValue>::
data(const std::size_t rowIndex, const std::size_t columnIndex)
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
