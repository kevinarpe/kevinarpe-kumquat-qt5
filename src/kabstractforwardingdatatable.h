//
// Created by kca on 5/10/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KAFORWARDINGDATATABLE_H
#define KEVINARPE_KUMQUAT_QT5_KAFORWARDINGDATATABLE_H

#include "KIDataTable"

namespace kumquat {

template<typename TValue>
class KAbstractForwardingDataTable
    : public KIDataTable<TValue> {

private:
    typedef KIDataTable<TValue> Base;

public:
    KAbstractForwardingDataTable()
        : Base()
    { }

    virtual ~KAbstractForwardingDataTable()
    { }

    virtual std::size_t
    rowCount()
    const override;

    virtual std::size_t
    columnCount()
    const override;

    virtual const TValue&
    data(const std::size_t rowIndex, const std::size_t columnIndex)
    const override;

    virtual const TValue&
    headerData(const std::size_t index, Qt::Orientation orientation)
    const override;

protected:
    virtual const KIDataTable<TValue>&
    dataTableDelegate()
    const = 0;
};

}  // namespace kumquat

#include "kabstractforwardingdatatable.impl.h"

#endif //KEVINARPE_KUMQUAT_QT5_KAFORWARDINGDATATABLE_H
