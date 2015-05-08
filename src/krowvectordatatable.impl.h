//
// Created by kca on 5/2/15.
//

#include "krowvectordatatable.h"
#include "kfunctional.h"

namespace kumquat {

// public
// Ref: http://stackoverflow.com/a/8114913/257299
template<typename TValue>
KRowVectorDataTable<TValue>::
KRowVectorDataTable(TableHeaderPtr horizontalTableHeader,
                    TableHeaderPtr verticalTableHeader)

    : Base(),
      _orientation_To_TableHeaderPtr_Map(_newMap(horizontalTableHeader, verticalTableHeader))
{ }

// TODO: Ask a question on StackOverflow about the difference between:
// (a) const x& -- does not work
// (b) x& -- works
// (c) x -- works
// (d) x&& -- did not try
// private static
template<typename TValue>
typename KRowVectorDataTable<TValue>::QtOrientation_To_TableHeaderPtr_Map
KRowVectorDataTable<TValue>::
_newMap(TableHeaderPtr& horizontalTableHeader,
        TableHeaderPtr& verticalTableHeader) {
    // Ref: http://stackoverflow.com/a/21057289/257299
    typedef typename QtOrientation_To_TableHeaderPtr_Map::value_type MapValueType;

    QtOrientation_To_TableHeaderPtr_Map map;
    map.insert(MapValueType(Qt::Horizontal, std::move(horizontalTableHeader)));
    map.insert(MapValueType(Qt::Vertical, std::move(verticalTableHeader)));
    return map;
}

// public virtual
template<typename TValue>
std::size_t
KRowVectorDataTable<TValue>::
rowCount()
const /*override*/ {
    const std::size_t x = _dataMatrix.rowCount();
    return x;
}

// public virtual
template<typename TValue>
std::size_t
KRowVectorDataTable<TValue>::
columnCount()
const /*override*/ {
    const std::size_t x = _dataMatrix.columnCount();
    return x;
}

// public virtual
template<typename TValue>
const TValue&
KRowVectorDataTable<TValue>::
data(std::size_t rowIndex, std::size_t columnIndex)
const /*override*/ {
    const TValue& x = _dataMatrix.data(rowIndex, columnIndex);
    return x;
}

// public virtual
template<typename TValue>
const TValue&
KRowVectorDataTable<TValue>::
headerData(const std::size_t index, Qt::Orientation orientation)
const /*override*/ {
    const TableHeaderPtr& tableHeader = _orientation_To_TableHeaderPtr_Map.at(orientation);
    const TValue& x = tableHeader->data(index);
    return x;
}

// public virtual
template<typename TValue>
typename KRowVectorDataTable<TValue>::Self&
KRowVectorDataTable<TValue>::
appendRow(const RowVec& rowVec) {
    _dataMatrix.appendRow(rowVec);
    return *this;
}

}  // namespace kumquat
