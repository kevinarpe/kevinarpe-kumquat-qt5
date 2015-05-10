//
// Created by kca on 5/3/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KAUTONUMBEREDTABLEHEADER_H
#define KEVINARPE_KUMQUAT_QT5_KAUTONUMBEREDTABLEHEADER_H

#include "KITableHeader"
#include <vector>

namespace kumquat {

template<typename TValue>
class KAutoNumberedTableHeader
    : public KITableHeader<TValue> {

private:
    typedef KITableHeader<TValue> Base;

public:
    KAutoNumberedTableHeader()
    : Base()
    { }

    virtual
    ~KAutoNumberedTableHeader()
    { }

    virtual const TValue&
    data(const std::size_t index)
    const override;

private:
    mutable std::vector<TValue> _headerData;
};

}  // namespace kumquat

#include "kautonumberedtableheader.impl.h"

#endif //KEVINARPE_KUMQUAT_QT5_KAUTONUMBEREDTABLEHEADER_H
