//
// Created by kca on 5/2/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KVECTORTABLEHEADER_H
#define KEVINARPE_KUMQUAT_QT5_KVECTORTABLEHEADER_H

#include "kabstracttableheader.h"
#include <vector>

namespace kumquat {

template<typename TValue>
class KVectorTableHeader
    : public KAbstractTableHeader<TValue> {

private:
    typedef KAbstractTableHeader<TValue> Base;

public:
    explicit KVectorTableHeader(const std::vector<TValue>& headerData)
    : Base(),
      _headerData(headerData)
    { }

    virtual
    ~KVectorTableHeader()
    { }

public:
    virtual const TValue&
    data(const std::size_t index)
    const override;

private:
    // Intentional: Not a const ref; copy the ctor value.
    const std::vector<TValue> _headerData;
};

}  // namespace kumquat

#include "kvectortableheader.impl.h"

#endif //KEVINARPE_KUMQUAT_QT5_KVECTORTABLEHEADER_H
