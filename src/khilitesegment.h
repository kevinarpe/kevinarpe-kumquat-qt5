//
// Created by kca on 5/9/15.
//

#ifndef KEVINARPE_KUMQUAT_QT5_KHILITESEGMENT_H
#define KEVINARPE_KUMQUAT_QT5_KHILITESEGMENT_H

#include <Qt>

namespace kumquat {

class KHiliteSegment {

public:
    static KHiliteSegment fromIndexAndCount(int index, int count) {
        const KHiliteSegment x = KHiliteSegment(index, count);
        return x;
    }

    KHiliteSegment()
        : _index(INVALID_VALUE),
          _count(INVALID_VALUE)
    { }

    int
    index()
    const {
        Q_ASSERT(INVALID_VALUE != _index);
        return _index;
    }

    int
    count()
    const {
        Q_ASSERT(INVALID_VALUE != _count);
        return _count;
    }

private:
    static const int INVALID_VALUE = int(-1);

    int _index;
    int _count;

    KHiliteSegment(int index, int count)
        : _index(index), _count(count)
    { }
};

}  // namespace kumquat

#endif //KEVINARPE_KUMQUAT_QT5_KHILITESEGMENT_H
