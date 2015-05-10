//
// Created by kca on 5/2/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KABSTRACTDATATABLE_H
#define KEVINARPE_KUMQUAT_QT5_KABSTRACTDATATABLE_H

#include "KIDataMatrix"
#include <Qt>

namespace kumquat {

template<typename TValue>
class KIDataTable
    : public KIDataMatrix<TValue> {

private:
    typedef KIDataMatrix<TValue> Base;

public:
    KIDataTable()
    : Base()
    { }

    virtual
    ~KIDataTable() { }

    virtual const TValue&
    headerData(const std::size_t index, Qt::Orientation orientation)
    const = 0;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KABSTRACTDATATABLE_H
