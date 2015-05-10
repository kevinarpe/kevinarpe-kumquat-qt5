//
// Created by kca on 5/2/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KABSTRACTTABLEHEADER_H
#define KEVINARPE_KUMQUAT_QT5_KABSTRACTTABLEHEADER_H

#include <cstddef>

namespace kumquat {

template<typename TValue>
class KITableHeader {

public:
    KITableHeader()
    { }

    virtual
    ~KITableHeader()
    { }

    virtual const TValue&
    data(const std::size_t index)
    const = 0;
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KABSTRACTTABLEHEADER_H
