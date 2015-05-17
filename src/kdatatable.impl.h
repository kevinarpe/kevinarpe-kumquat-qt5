//
// Created by kca on 5/16/15.
//

#include "KDataTable"
#include "KFixedSizeMap"

namespace kumquat {

// public
template<typename TValue, typename TDataMatrix>
KDataTable<TValue, TDataMatrix>::
KDataTable(TableHeaderPtr horizontalTableHeaderPtr,
           TableHeaderPtr verticalTableHeaderPtr,
           DataMatrixPtr dataMatrixPtr)
      : _orientation_To_TableHeaderPtr_Map(
            {
                { Qt::Horizontal, std::move(horizontalTableHeaderPtr) },
                { Qt::Vertical, std::move(verticalTableHeaderPtr) },
            }),
      _dataMatrixPtr(std::move(dataMatrixPtr))
{ }

// public
template<typename TValue, typename TDataMatrix>
std::size_t
KDataTable<TValue, TDataMatrix>::
size(Dimension dim)
const {
    const std::size_t x = _dataMatrixPtr->size(dim);
    return x;
}

// public
template<typename TValue, typename TDataMatrix>
typename KDataTable<TValue, TDataMatrix>::const_iterator
KDataTable<TValue, TDataMatrix>::
begin()
const {
    const const_iterator x = _dataMatrixPtr->begin();
    return x;
}

// public
template<typename TValue, typename TDataMatrix>
typename KDataTable<TValue, TDataMatrix>::const_iterator
KDataTable<TValue, TDataMatrix>::
end()
const {
    const const_iterator x = _dataMatrixPtr->end();
    return x;
}

// public
template<typename TValue, typename TDataMatrix>
const TValue&
KDataTable<TValue, TDataMatrix>::
data(const std::size_t rowIndex, const std::size_t columnIndex)
const {
    const TValue& x = _dataMatrixPtr->data(rowIndex, columnIndex);
    return x;
}

// public
template<typename TValue, typename TDataMatrix>
typename KDataTable<TValue, TDataMatrix>::Self&
KDataTable<TValue, TDataMatrix>::
append(std::initializer_list<TValue> list) {
    _dataMatrixPtr->append(list);
    return *this;
}

// public
template<typename TValue, typename TDataMatrix>
template<typename InputIter>
typename KDataTable<TValue, TDataMatrix>::Self&
KDataTable<TValue, TDataMatrix>::
append(InputIter first, InputIter last) {
    _dataMatrixPtr->append(first, last);
    return *this;
}

// public
template<typename TValue, typename TDataMatrix>
const TValue&
KDataTable<TValue, TDataMatrix>::
headerData(const std::size_t index, const Qt::Orientation orientation)
const {
    const _TableHeaderPtr& tableHeader = _orientation_To_TableHeaderPtr_Map[orientation];
    const TValue& x = tableHeader->data(index);
    return x;
}

}  // namespace kumquat
