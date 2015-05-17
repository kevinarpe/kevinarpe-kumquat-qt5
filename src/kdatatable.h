//
// Created by kca on 5/16/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KDATATABLE_H
#define KEVINARPE_KUMQUAT_QT5_KDATATABLE_H

#include "KITableHeader"
#include "KRowDataMatrix"
#include "KFixedSizeMap"
#include <memory>
#include <unordered_map>

namespace kumquat {

template<
    typename TValue,
    typename TDataMatrix = KRowDataMatrix<TValue>
>
class KDataTable {

public:
    typedef KITableHeader<TValue> TableHeader;
    typedef std::unique_ptr<TableHeader> TableHeaderPtr;
    typedef TDataMatrix DataMatrix;
    typedef std::unique_ptr<DataMatrix> DataMatrixPtr;
    typedef KDataTable<TValue, TDataMatrix> Self;
    typedef typename DataMatrix::const_iterator const_iterator;

    KDataTable(TableHeaderPtr horizontalTableHeaderPtr,
               TableHeaderPtr verticalTableHeaderPtr,
               DataMatrixPtr dataMatrixPtr);

    std::size_t
    size(const Dimension dim)
    const;

    const_iterator
    begin()
    const;

    const_iterator
    end()
    const;

    const TValue&
    data(const std::size_t rowIndex, const std::size_t columnIndex)
    const;

    Self&
    append(std::initializer_list<TValue> list);

    template<typename InputIter>
    Self&
    append(InputIter first, InputIter last);

    const TValue&
    headerData(const std::size_t index, const Qt::Orientation orientation)
    const;

private:
    // Intentional: Shift from unique_ptr to shared_ptr.
    // I cannot make sorting work with unique_ptr in a container.  Try shared_ptr.
    typedef std::shared_ptr<TableHeader> _TableHeaderPtr;
    typedef KFixedSizeMap<Qt::Orientation, _TableHeaderPtr> _QtOrientation_To_TableHeaderPtr_Map;

    // TODO: Can this be const?
    _QtOrientation_To_TableHeaderPtr_Map _orientation_To_TableHeaderPtr_Map;
    DataMatrixPtr _dataMatrixPtr;
};

}  // namespace kumquat

#include "kdatatable.impl.h"

#endif //KEVINARPE_KUMQUAT_QT5_KDATATABLE_H
