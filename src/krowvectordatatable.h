//
// Created by kca on 5/2/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KROWVECTORDATATABLE_H
#define KEVINARPE_KUMQUAT_QT5_KROWVECTORDATATABLE_H

#include "kabstracttableheader.h"
#include "kabstractdatatable.h"
#include "krowvectordatamatrix.h"

#include <functional>
#include <unordered_map>
#include <memory>

namespace kumquat {

template<typename TValue>
class KRowVectorDataTable : public KAbstractDataTable<TValue> {

private:
    typedef KAbstractDataTable<TValue> Base;

public:
    typedef KRowVectorDataTable<TValue> Self;
    typedef typename KRowVectorDataMatrix<TValue>::RowVec RowVec;
    typedef KAbstractTableHeader<TValue> TableHeader;
    typedef std::unique_ptr<TableHeader> TableHeaderPtr;

    KRowVectorDataTable(TableHeaderPtr horizontalTableHeader,
                        TableHeaderPtr verticalTableHeader);

    virtual
    ~KRowVectorDataTable()
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

    virtual const TValue&
    headerData(const std::size_t index, Qt::Orientation orientation)
    const override;

    virtual Self&
    appendRow(const RowVec& rowVec);

private:
    typedef std::unordered_map<Qt::Orientation, TableHeaderPtr> QtOrientation_To_TableHeaderPtr_Map;
    const QtOrientation_To_TableHeaderPtr_Map _orientation_To_TableHeaderPtr_Map;
    KRowVectorDataMatrix<TValue> _dataMatrix;

    static QtOrientation_To_TableHeaderPtr_Map
    _newMap(TableHeaderPtr& horizontalTableHeader,
            TableHeaderPtr& verticalTableHeader);
};

}  // namespace kumquat

#include "krowvectordatatable.impl.h"

#endif //KEVINARPE_KUMQUAT_QT5_KROWVECTORDATATABLE_H
