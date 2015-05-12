//
// Created by kca on 5/10/15.
//

#include "KAbstractForwardingDataTable"

namespace kumquat {

// public virtual
template<typename TValue>
std::size_t
KAbstractForwardingDataTable<TValue>::
rowCount()
const /*override*/ {
    const KIDataTable<TValue>& delegate = dataTableDelegate();
    const std::size_t x = delegate.rowCount();
    return x;
}

// public virtual
template<typename TValue>
std::size_t
KAbstractForwardingDataTable<TValue>::
columnCount()
const /*override*/ {
    const KIDataTable<TValue>& delegate = dataTableDelegate();
    const std::size_t x = delegate.columnCount();
    return x;
}

// public virtual
template<typename TValue>
const TValue&
KAbstractForwardingDataTable<TValue>::
data(const std::size_t rowIndex, const std::size_t columnIndex)
const /*override*/ {
    const KIDataTable<TValue>& delegate = dataTableDelegate();
    const TValue& x = delegate.data(rowIndex, columnIndex);
    return x;
}

// public virtual
template<typename TValue>
const TValue&
KAbstractForwardingDataTable<TValue>::
headerData(const std::size_t index, Qt::Orientation orientation)
const /*override*/ {
    const KIDataTable<TValue>& delegate = dataTableDelegate();
    const TValue& x = delegate.headerData(index, orientation);
    return x;
}

}  // namespace kumquat
