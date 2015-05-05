//
// Created by kca on 5/2/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KABSTRACTDATATABLE_H
#define KEVINARPE_KUMQUAT_QT5_KABSTRACTDATATABLE_H

#include "kabstractdatamatrix.h"
#include <Qt>

namespace kumquat {

template<typename TValue>
class KAbstractDataTable : public KAbstractDataMatrix<TValue> {

private:
    typedef KAbstractDataMatrix<TValue> Base;

public:
    KAbstractDataTable()
    : Base()
    { }

    virtual
    ~KAbstractDataTable() { }

    virtual const TValue&
    headerData(const std::size_t index, Qt::Orientation orientation)
    const = 0;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KABSTRACTDATATABLE_H
