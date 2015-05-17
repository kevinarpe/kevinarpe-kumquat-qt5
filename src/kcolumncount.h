//
// Created by kca on 5/17/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KCOLUMNCOUNT_H
#define KEVINARPE_KUMQUAT_QT5_KCOLUMNCOUNT_H

#include <cstdlib>
#include <cassert>

namespace kumquat {

class KColumnCount {

public:
    KColumnCount(const std::size_t columnCount)
        : value(_check(columnCount))
    { }

    const std::size_t value;

private:
    std::size_t
    _check(const std::size_t columnCount) {
        assert(columnCount > 0 && "Argument 'columnCount' must be positive");
        return columnCount;
    }
};

}  // namespace kumquat


#endif //KEVINARPE_KUMQUAT_QT5_KCOLUMNCOUNT_H
