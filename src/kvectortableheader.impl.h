//
// Created by kca on 5/9/15.
//

#include "kvectortableheader.h"

namespace kumquat {

// TODO: Open youtrack bug for 'override' keyword... no IDE error if *not* commented-out
// error: virt-specifiers in ‘data’ not allowed outside a class definition

// public virtual
template<typename TValue>
const TValue&
KVectorTableHeader<TValue>::
data(const std::size_t index)
const /*override*/ {
    const TValue& x = _headerData.at(index);
    return x;
}

}  // namespace kumquat
